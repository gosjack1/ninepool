"""Self-test for force_model.py.

Runs without Optuna and without touching the shipped calibration_data.yaml:
every case builds a temporary YAML fixture and points ForceModel at it.

Verifies:
  * empty calibration -> recommend_tier() raises (never a default guess)
  * main-only data -> aux queries raise, never fall back on main
  * low-R^2 samples are filtered out of get_calibrated_speed() statistics
  * three-tier boundary behaviour (distance exactly on a threshold)

Prints an "all tests passed" / failed-list summary and exits non-zero on any
failure, matching the "force_model.py self-test all pass" acceptance bar.
"""

from __future__ import annotations

import sys
import tempfile
import traceback
from pathlib import Path

import yaml

from force_model import (
    ForceModel,
    InsufficientCalibration,
    MIN_R_SQUARED,
)


# --- fixture helpers ----------------------------------------------------------
def _write_yaml(tmpdir: Path, doc: dict) -> Path:
    path = tmpdir / "calibration_data.yaml"
    with open(path, "w") as f:
        yaml.safe_dump(doc, f, sort_keys=False, allow_unicode=True)
    return path


def _trial(trial_id, solenoid, tier, v0, r2, direction=0.0):
    return {
        "trial_id": trial_id,
        "solenoid": solenoid,
        "voltage_tier": tier,
        "v0_mm_s": v0,
        "direction_deg": direction,
        "r_squared": r2,
        "n_frames_used": 6,
        "timestamp": "2026-07-29T12:00:00+00:00",
    }


def _empty_thresholds():
    return {
        "main": {"weak_max_distance_mm": None, "medium_max_distance_mm": None},
        "aux": {"weak_max_distance_mm": None, "medium_max_distance_mm": None},
    }


# --- test cases ---------------------------------------------------------------
def test_empty_raises(tmp: Path):
    """No trials / null thresholds -> recommend_tier must raise, not guess."""
    path = _write_yaml(tmp, {"trials": [], "thresholds": _empty_thresholds()})
    model = ForceModel(data_path=path)
    for solenoid in ("main", "aux"):
        try:
            tier = model.recommend_tier(solenoid, 500.0)
        except InsufficientCalibration:
            pass
        else:
            raise AssertionError(
                f"expected InsufficientCalibration for un-calibrated {solenoid!r}, "
                f"got {tier!r}"
            )


def test_no_cross_fallback(tmp: Path):
    """main calibrated, aux empty -> aux queries must raise (no fallback)."""
    thresholds = _empty_thresholds()
    thresholds["main"] = {
        "weak_max_distance_mm": 300.0,
        "medium_max_distance_mm": 800.0,
    }
    doc = {
        "trials": [
            _trial(1, "main", "weak", 900.0, 0.97),
            _trial(2, "main", "medium", 1500.0, 0.95),
        ],
        "thresholds": thresholds,
    }
    path = _write_yaml(tmp, doc)
    model = ForceModel(data_path=path)

    # main works...
    assert model.recommend_tier("main", 200.0) == "weak"
    # ...aux must NOT borrow main's thresholds.
    try:
        model.recommend_tier("aux", 200.0)
    except InsufficientCalibration:
        pass
    else:
        raise AssertionError("aux recommend_tier must raise, not fall back on main")

    # aux speed query with no aux samples must also raise.
    try:
        model.get_calibrated_speed("aux", "weak")
    except InsufficientCalibration:
        pass
    else:
        raise AssertionError("aux get_calibrated_speed must raise with no aux data")


def test_low_r_squared_filtered(tmp: Path):
    """Samples below MIN_R_SQUARED must not enter get_calibrated_speed stats."""
    good = [1000.0, 1010.0, 990.0]  # r2 = 0.95
    bad_low = 5000.0                # r2 = 0.50 -> discarded
    bad_edge = 4000.0               # r2 = 0.79 (< 0.8) -> discarded
    trials = [
        _trial(1, "main", "medium", good[0], 0.95),
        _trial(2, "main", "medium", good[1], 0.95),
        _trial(3, "main", "medium", good[2], 0.95),
        _trial(4, "main", "medium", bad_low, 0.50),
        _trial(5, "main", "medium", bad_edge, 0.79),
        # exactly at the cutoff should be KEPT (filter is strict <).
        _trial(6, "main", "medium", 1005.0, MIN_R_SQUARED),
    ]
    path = _write_yaml(tmp, {"trials": trials, "thresholds": _empty_thresholds()})
    model = ForceModel(data_path=path)

    assert model.valid_sample_count("main", "medium") == 4, (
        f"expected 4 kept samples, got {model.valid_sample_count('main', 'medium')}"
    )
    mean_v0, std_v0 = model.get_calibrated_speed("main", "medium")
    kept = good + [1005.0]
    expected_mean = sum(kept) / len(kept)
    assert abs(mean_v0 - expected_mean) < 1e-6, (
        f"low-R^2 samples leaked into mean: {mean_v0} != {expected_mean}"
    )
    # The discarded 4000-5000 mm/s outliers would have inflated the mean well
    # past 1500; a clean mean proves they were filtered.
    assert mean_v0 < 1500.0
    assert std_v0 >= 0.0


def test_tier_boundaries(tmp: Path):
    """Distance exactly on a threshold selects the lower tier."""
    thresholds = {
        "main": {"weak_max_distance_mm": 300.0, "medium_max_distance_mm": 800.0},
        "aux": {"weak_max_distance_mm": None, "medium_max_distance_mm": None},
    }
    path = _write_yaml(tmp, {"trials": [], "thresholds": thresholds})
    model = ForceModel(data_path=path)

    checks = [
        (0.0, "weak"),
        (299.999, "weak"),
        (300.0, "weak"),       # exactly weak_max -> weak (lower tier)
        (300.001, "medium"),
        (799.999, "medium"),
        (800.0, "medium"),     # exactly medium_max -> medium (lower tier)
        (800.001, "strong"),
        (5000.0, "strong"),
    ]
    for distance, expected in checks:
        got = model.recommend_tier("main", distance)
        assert got == expected, (
            f"distance {distance}mm -> expected {expected!r}, got {got!r}"
        )


def test_speed_stats_values(tmp: Path):
    """mean/std are the sample statistics of the kept speeds."""
    trials = [
        _trial(1, "aux", "strong", 700.0, 0.9),
        _trial(2, "aux", "strong", 720.0, 0.9),
        _trial(3, "aux", "strong", 680.0, 0.9),
    ]
    path = _write_yaml(tmp, {"trials": trials, "thresholds": _empty_thresholds()})
    model = ForceModel(data_path=path)
    mean_v0, std_v0 = model.get_calibrated_speed("aux", "strong")
    assert abs(mean_v0 - 700.0) < 1e-9, mean_v0
    assert std_v0 > 0.0, "three distinct samples must have non-zero std"

    # main must be independent of aux (empty here).
    try:
        model.get_calibrated_speed("main", "strong")
    except InsufficientCalibration:
        pass
    else:
        raise AssertionError("main speed query must raise; aux data must not leak")


def test_bad_arguments(tmp: Path):
    """Unknown solenoid / tier raise ValueError; negative distance rejected."""
    path = _write_yaml(tmp, {"trials": [], "thresholds": _empty_thresholds()})
    model = ForceModel(data_path=path)
    for bad_call in (
        lambda: model.recommend_tier("side", 100.0),
        lambda: model.get_calibrated_speed("main", "turbo"),
        lambda: model.get_calibrated_speed("nope", "weak"),
    ):
        try:
            bad_call()
        except ValueError:
            pass
        else:
            raise AssertionError("expected ValueError for bad argument")

    # negative distance -> ValueError (even before calibration check)
    thresholds = {
        "main": {"weak_max_distance_mm": 300.0, "medium_max_distance_mm": 800.0},
        "aux": {"weak_max_distance_mm": None, "medium_max_distance_mm": None},
    }
    path2 = _write_yaml(tmp, {"trials": [], "thresholds": thresholds})
    model2 = ForceModel(data_path=path2)
    try:
        model2.recommend_tier("main", -1.0)
    except ValueError:
        pass
    else:
        raise AssertionError("negative distance must raise ValueError")


# --- runner -------------------------------------------------------------------
TESTS = [
    test_empty_raises,
    test_no_cross_fallback,
    test_low_r_squared_filtered,
    test_tier_boundaries,
    test_speed_stats_values,
    test_bad_arguments,
]


def main() -> int:
    passed: list[str] = []
    failed: list[tuple[str, str]] = []
    with tempfile.TemporaryDirectory() as td:
        tmp = Path(td)
        for test in TESTS:
            try:
                test(tmp)
            except Exception:
                failed.append((test.__name__, traceback.format_exc()))
            else:
                passed.append(test.__name__)

    print("=" * 60)
    print(f"solenoid_force_model self-test: {len(passed)}/{len(TESTS)} passed")
    for name in passed:
        print(f"  [PASS] {name}")
    for name, tb in failed:
        print(f"  [FAIL] {name}")
        print("    " + tb.replace("\n", "\n    ").rstrip())

    if failed:
        print("\nRESULT: FAILED (" + ", ".join(n for n, _ in failed) + ")")
        return 1
    print("\nRESULT: all tests passed")
    return 0


if __name__ == "__main__":
    sys.exit(main())
