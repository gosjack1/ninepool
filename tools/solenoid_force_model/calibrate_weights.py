"""Fit per-solenoid distance thresholds from calibration_data.yaml with Optuna.

For each solenoid (main / aux, kept independent) this reads the recorded
``trials``, keeps only the reliable ones (R^2 >= MIN_R_SQUARED), and fits the
two distance cut points (``weak_max_distance_mm`` / ``medium_max_distance_mm``)
that split target distances into the three force tiers.

Objective
---------
Each measured shot is a pair (voltage_tier, v0_mm_s).  A shot's initial speed
implies how far the ball rolls before stopping, under a constant-deceleration
model::

    reach_distance = v0**2 / (2 * DECEL_MM_S2)

Given candidate thresholds we decide a tier from that reach distance
(exactly as ForceModel.recommend_tier would), predict the speed of that tier
(the mean v0 of samples actually recorded at that tier), and accumulate the
squared error against the shot's real v0.  Optuna minimises the total SSE.

Sample-size guard
-----------------
Threshold fits on tiny samples are worthless.  Weight calibration for
nine_ball_strat.py showed Optuna thrashing when n < 30 (angle_weight jumped
between ~20 and ~661 across runs).  The same instability applies here, so every
tier of a solenoid must have at least MIN_SAMPLES_PER_TIER reliable samples; a
solenoid that falls short is skipped with a warning rather than fitted on thin
data.
"""

from __future__ import annotations

import argparse
import statistics
from pathlib import Path
from typing import Optional

import yaml

from force_model import (
    MIN_R_SQUARED,
    SOLENOIDS,
    TIERS,
)

# Minimum reliable (R^2-passing) samples required *per tier per solenoid*
# before we trust a fit.  See module docstring for the n<30 thrashing history.
MIN_SAMPLES_PER_TIER: int = 15

# Constant-deceleration coefficient (mm/s^2) mapping an initial speed to the
# distance the ball rolls before stopping (reach_distance = v0^2/(2*DECEL)).
# It only sets the distance *scale* the thresholds live on; the tier decisions
# it drives are scale-invariant, so a rough value is fine.
DECEL_MM_S2: float = 300.0

# Optuna trials for the threshold search.
N_OPTUNA_TRIALS: int = 400

_DATA_PATH = Path(__file__).resolve().parent / "calibration_data.yaml"


def _reach_distance_mm(v0_mm_s: float) -> float:
    """Distance the ball rolls before stopping, from its initial speed."""
    return (float(v0_mm_s) ** 2) / (2.0 * DECEL_MM_S2)


def _decide_tier(distance_mm: float, weak_max: float, medium_max: float) -> str:
    """Same boundary rule as ForceModel.recommend_tier (equal -> lower tier)."""
    if distance_mm <= weak_max:
        return "weak"
    if distance_mm <= medium_max:
        return "medium"
    return "strong"


def _load() -> dict:
    with open(_DATA_PATH, "r") as f:
        return yaml.safe_load(f) or {}


def _group_valid_trials(data: dict) -> dict[str, list[dict]]:
    """Group R^2-passing trials by solenoid."""
    grouped: dict[str, list[dict]] = {s: [] for s in SOLENOIDS}
    for trial in data.get("trials") or []:
        solenoid = trial.get("solenoid")
        if solenoid not in SOLENOIDS:
            continue
        r_squared = trial.get("r_squared")
        if r_squared is None or float(r_squared) < MIN_R_SQUARED:
            continue
        if trial.get("v0_mm_s") is None or trial.get("voltage_tier") not in TIERS:
            continue
        grouped[solenoid].append(trial)
    return grouped


def _fit_one(solenoid: str, trials: list[dict]) -> Optional[dict[str, float]]:
    """Fit (weak_max, medium_max) for one solenoid, or None if skipped."""
    import optuna  # imported lazily so force_model/tests never need Optuna

    # Per-tier sample-size gate.
    counts = {tier: sum(1 for t in trials if t["voltage_tier"] == tier) for tier in TIERS}
    thin = {tier: n for tier, n in counts.items() if n < MIN_SAMPLES_PER_TIER}
    if thin:
        print(
            f"[skip] solenoid={solenoid!r}: insufficient samples per tier "
            f"{counts} (need >= {MIN_SAMPLES_PER_TIER} each); "
            f"tiers below threshold: {thin}. Collect more data before fitting."
        )
        return None

    # Per-tier mean speed = the speed we would predict for that tier.
    tier_mean_speed = {
        tier: statistics.fmean(
            float(t["v0_mm_s"]) for t in trials if t["voltage_tier"] == tier
        )
        for tier in TIERS
    }

    samples = [(_reach_distance_mm(t["v0_mm_s"]), float(t["v0_mm_s"])) for t in trials]
    d_min = min(d for d, _ in samples)
    d_max = max(d for d, _ in samples)

    def objective(trial: "optuna.Trial") -> float:
        weak_max = trial.suggest_float("weak_max_distance_mm", d_min, d_max)
        # Keep ordering weak_max <= medium_max by construction.
        medium_max = trial.suggest_float("medium_max_distance_mm", weak_max, d_max)
        sse = 0.0
        for distance_mm, actual_v0 in samples:
            tier = _decide_tier(distance_mm, weak_max, medium_max)
            predicted = tier_mean_speed[tier]
            sse += (predicted - actual_v0) ** 2
        return sse

    optuna.logging.set_verbosity(optuna.logging.WARNING)
    study = optuna.create_study(direction="minimize")
    study.optimize(objective, n_trials=N_OPTUNA_TRIALS, show_progress_bar=False)

    weak_max = float(study.best_params["weak_max_distance_mm"])
    medium_max = float(study.best_params["medium_max_distance_mm"])
    print(
        f"[ok]  solenoid={solenoid!r}: weak_max={weak_max:.1f}mm "
        f"medium_max={medium_max:.1f}mm  (SSE={study.best_value:.1f}, "
        f"n={len(trials)}, per-tier={counts})"
    )
    return {
        "weak_max_distance_mm": round(weak_max, 3),
        "medium_max_distance_mm": round(medium_max, 3),
    }


def calibrate(write: bool = True) -> dict[str, Optional[dict[str, float]]]:
    """Fit thresholds for every solenoid and (optionally) write them back."""
    data = _load()
    grouped = _group_valid_trials(data)

    results: dict[str, Optional[dict[str, float]]] = {}
    for solenoid in SOLENOIDS:
        trials = grouped[solenoid]
        if not trials:
            print(f"[skip] solenoid={solenoid!r}: no reliable trials found.")
            results[solenoid] = None
            continue
        results[solenoid] = _fit_one(solenoid, trials)

    if write:
        thresholds = data.get("thresholds") or {}
        for solenoid in SOLENOIDS:
            slot = thresholds.setdefault(
                solenoid,
                {"weak_max_distance_mm": None, "medium_max_distance_mm": None},
            )
            fit = results[solenoid]
            if fit is not None:
                slot["weak_max_distance_mm"] = fit["weak_max_distance_mm"]
                slot["medium_max_distance_mm"] = fit["medium_max_distance_mm"]
            # Solenoids that were skipped keep whatever was already stored.
        data["thresholds"] = thresholds
        with open(_DATA_PATH, "w") as f:
            yaml.safe_dump(data, f, sort_keys=False, allow_unicode=True)
        print(f"[write] thresholds written to {_DATA_PATH}")

    return results


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="fit thresholds but do not write them back to calibration_data.yaml",
    )
    args = parser.parse_args()
    calibrate(write=not args.dry_run)


if __name__ == "__main__":
    main()
