"""Core solenoid force model: target distance -> recommended tier / speed.

The nine-ball arm drives the cue with two solenoids in two incompatible
voltage regimes:

    main : primary strike solenoid (48V)
    aux  : auxiliary solenoid      (12V / 24V)

Each regime is characterised by three discrete force tiers -- weak / medium /
strong -- and by distance thresholds that say which tier to use for a given
target travel distance.  main and aux are kept strictly separate: they are
never allowed to fall back on one another, because a threshold or speed learnt
in one voltage regime is meaningless in the other.

This module only reads its own data file (``calibration_data.yaml``, which
lives next to this file); it does not touch ``arm.yaml``.  Should a future
consumer need the shared project config it should go through the project's
``resolve_config_path('arm.yaml')`` convention rather than hard-coding a path.
"""

from __future__ import annotations

import statistics
from pathlib import Path
from typing import Optional

import yaml

# --- project-wide conventions -------------------------------------------------
# Physical ball radius, in millimetres.  This is the real ball radius used by
# the physics here -- do NOT confuse it with ``rb`` in base_strat.py, which is a
# pixel/display radius for a completely different (rendering) purpose.
R_BALL_MM: float = 19.0

# Angles that appear in trial data (``direction_deg``) are stored in degrees for
# human readability, but every internal computation is done in radians; degrees
# only ever appear at the I/O boundary.  (This module currently exposes no angle
# outputs, so no conversion is performed here -- the note is kept so future
# additions follow the radian-internally convention and avoid the deg/rad mixing
# bug that once bit simple_route().)

# --- calibration constants ----------------------------------------------------
SOLENOIDS = ("main", "aux")
TIERS = ("weak", "medium", "strong")

# Extrapolated-speed samples whose linear-regression R^2 is below this value are
# considered unreliable and are discarded before any statistic is computed.
MIN_R_SQUARED: float = 0.8

# calibration_data.yaml is this sub-module's own data and always lives right
# next to this file, so the path is intentionally fixed here (it is not managed
# by arm.yaml).
_DEFAULT_DATA_PATH = Path(__file__).resolve().parent / "calibration_data.yaml"


class InsufficientCalibration(RuntimeError):
    """Raised when a solenoid lacks the calibration needed to answer a query.

    We raise loudly rather than silently returning a guessed tier/speed: an
    un-calibrated regime must never be used to drive real hardware.
    """


class ForceModel:
    """Distance -> tier / speed model, keyed independently by solenoid.

    Parameters
    ----------
    data_path:
        Optional override for the calibration YAML.  Defaults to the
        ``calibration_data.yaml`` shipped alongside this module.
    """

    def __init__(self, data_path: Optional[Path | str] = None) -> None:
        self.data_path = Path(data_path) if data_path is not None else _DEFAULT_DATA_PATH
        # Per-solenoid stores -- deliberately independent, no cross-fallback.
        self._thresholds: dict[str, dict[str, Optional[float]]] = {}
        self._trials: dict[str, list[dict]] = {s: [] for s in SOLENOIDS}
        self.reload()

    # -- loading ---------------------------------------------------------------
    def reload(self) -> None:
        """(Re)load calibration_data.yaml, filtering out unreliable samples."""
        with open(self.data_path, "r") as f:
            data = yaml.safe_load(f) or {}

        raw_trials = data.get("trials") or []
        raw_thresholds = data.get("thresholds") or {}

        self._trials = {s: [] for s in SOLENOIDS}
        for trial in raw_trials:
            solenoid = trial.get("solenoid")
            if solenoid not in SOLENOIDS:
                # Unknown regime -- ignore rather than mis-file it under main/aux.
                continue
            r_squared = trial.get("r_squared")
            # Discard low-quality extrapolations; None/missing R^2 is untrusted.
            if r_squared is None or float(r_squared) < MIN_R_SQUARED:
                continue
            self._trials[solenoid].append(trial)

        self._thresholds = {}
        for solenoid in SOLENOIDS:
            t = raw_thresholds.get(solenoid) or {}
            self._thresholds[solenoid] = {
                "weak_max_distance_mm": t.get("weak_max_distance_mm"),
                "medium_max_distance_mm": t.get("medium_max_distance_mm"),
            }

    # -- helpers ---------------------------------------------------------------
    @staticmethod
    def _check_solenoid(solenoid: str) -> None:
        if solenoid not in SOLENOIDS:
            raise ValueError(
                f"unknown solenoid {solenoid!r}; expected one of {SOLENOIDS}"
            )

    # -- public API ------------------------------------------------------------
    def recommend_tier(self, solenoid: str, target_distance_mm: float) -> str:
        """Return the recommended force tier for *target_distance_mm*.

        Boundary rule: a distance exactly equal to a threshold selects the
        *lower* tier (``weak`` at ``weak_max``, ``medium`` at ``medium_max``).

        Raises
        ------
        InsufficientCalibration
            If *solenoid* has not been calibrated (thresholds still null).  We
            never guess, and we never borrow the other solenoid's thresholds.
        """
        self._check_solenoid(solenoid)
        if target_distance_mm < 0:
            raise ValueError("target_distance_mm must be non-negative")

        thr = self._thresholds[solenoid]
        weak_max = thr["weak_max_distance_mm"]
        medium_max = thr["medium_max_distance_mm"]

        if weak_max is None or medium_max is None:
            raise InsufficientCalibration(
                f"solenoid {solenoid!r} has no calibrated thresholds "
                f"(weak_max={weak_max}, medium_max={medium_max}); "
                f"run calibrate_weights.py after collecting enough trials."
            )
        if float(weak_max) > float(medium_max):
            raise InsufficientCalibration(
                f"solenoid {solenoid!r} thresholds are inconsistent: "
                f"weak_max={weak_max} > medium_max={medium_max}"
            )

        if target_distance_mm <= float(weak_max):
            return "weak"
        if target_distance_mm <= float(medium_max):
            return "medium"
        return "strong"

    def get_calibrated_speed(self, solenoid: str, tier: str) -> tuple[float, float]:
        """Return ``(mean_v0, std_v0)`` in mm/s for *solenoid* at *tier*.

        Only samples that survived the R^2 >= MIN_R_SQUARED filter are counted.
        ``std_v0`` is the sample standard deviation, or ``0.0`` when there is a
        single sample -- it gives the strategy engine a tolerance band.

        Raises
        ------
        InsufficientCalibration
            If there is no usable sample for this (solenoid, tier).
        """
        self._check_solenoid(solenoid)
        if tier not in TIERS:
            raise ValueError(f"unknown tier {tier!r}; expected one of {TIERS}")

        speeds = [
            float(t["v0_mm_s"])
            for t in self._trials[solenoid]
            if t.get("voltage_tier") == tier and t.get("v0_mm_s") is not None
        ]
        if not speeds:
            raise InsufficientCalibration(
                f"no usable samples for solenoid={solenoid!r} tier={tier!r} "
                f"(need R^2 >= {MIN_R_SQUARED})"
            )

        mean_v0 = statistics.fmean(speeds)
        std_v0 = statistics.stdev(speeds) if len(speeds) >= 2 else 0.0
        return (mean_v0, std_v0)

    def valid_sample_count(self, solenoid: str, tier: Optional[str] = None) -> int:
        """Number of R^2-passing samples for a solenoid (optionally a tier)."""
        self._check_solenoid(solenoid)
        trials = self._trials[solenoid]
        if tier is None:
            return len(trials)
        if tier not in TIERS:
            raise ValueError(f"unknown tier {tier!r}; expected one of {TIERS}")
        return sum(1 for t in trials if t.get("voltage_tier") == tier)


# --- lightweight self-check when run directly ---------------------------------
if __name__ == "__main__":
    model = ForceModel()
    print(f"loaded calibration from: {model.data_path}")
    for s in SOLENOIDS:
        counts = {tier: model.valid_sample_count(s, tier) for tier in TIERS}
        print(f"  {s}: valid samples by tier = {counts}")
