"""Solenoid force calibration model for the nine-ball robotic arm.

Discrete three-tier (weak / medium / strong) force calibration for the
primary strike solenoid (main, 48V) and the auxiliary solenoid (aux, 12V/24V).
The two voltage regimes are calibrated and stored completely independently.

Public API
----------
ForceModel                -- load calibration_data.yaml, recommend tiers / speeds
InsufficientCalibration   -- raised when a solenoid has no usable thresholds/data
"""

from .force_model import (
    ForceModel,
    InsufficientCalibration,
    R_BALL_MM,
    SOLENOIDS,
    TIERS,
    MIN_R_SQUARED,
)

__all__ = [
    "ForceModel",
    "InsufficientCalibration",
    "R_BALL_MM",
    "SOLENOIDS",
    "TIERS",
    "MIN_R_SQUARED",
]
