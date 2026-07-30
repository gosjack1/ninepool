"""
座標轉換層：機械手臂座標系 (mm, 對應 arm.yaml 校準) <-> PoolTool 桌面座標系 (m)

PoolTool 那邊的慣例(見 test_my_table.py 驗證過): 桌角是原點 (0, 0),
x 軸沿桌寬 w 方向, y 軸沿桌長 l 方向, 單位是公尺。

手臂那邊(nine_ball_strat.py / arm.yaml)是用手臂基座座標系, 單位 mm,
原點跟軸向由四個角袋(pot0~pot3)的實際量測位置決定, 跟 PoolTool 桌角
原點不是同一個點、軸向也不一定對齊, 所以需要這層轉換。

新桌的 pot0~pot3 還沒有校準值(舊 arm.yaml 是另一張小桌的), 所以這裡
不寫死任何角袋座標, ArmTableFrame 的角袋位置一律由外部傳入
(可以是新校準出的 arm.yaml, 也可以先用 placeholder 測試轉換邏輯本身對不對)。
"""

from dataclasses import dataclass, field

import numpy as np

MM_PER_M = 1000.0


def mm_to_m(value_mm):
    return np.asarray(value_mm, dtype=float) / MM_PER_M


def m_to_mm(value_m):
    return np.asarray(value_m, dtype=float) * MM_PER_M


@dataclass
class ArmTableFrame:
    """描述 PoolTool 桌面座標系跟手臂座標系之間的關係。

    origin_mm: PoolTool 原點 (0, 0) 對應到手臂座標系的位置 (mm, [x, y])。
               對應到 nine_ball_strat.py 裡的 hole_0(左下角袋)。
               ⚠️ placeholder: 新桌未校準前預設 [0, 0], 不代表真實值。
    x_axis_point_mm: 手臂座標系下, PoolTool x 軸(桌寬 w 方向)上另一個已知點
                      (例如右下角袋), 用來算出 x 軸的單位向量。
                      ⚠️ placeholder: 預設在 origin_mm 正右方 1 單位處。
    y_axis_point_mm: 手臂座標系下, PoolTool y 軸(桌長 l 方向)上另一個已知點
                      (例如左上角袋), 用來算出 y 軸的單位向量。
                      ⚠️ placeholder: 預設在 origin_mm 正上方 1 單位處。
    """

    origin_mm: np.ndarray = field(default_factory=lambda: np.array([0.0, 0.0]))
    x_axis_point_mm: np.ndarray = field(default_factory=lambda: np.array([1.0, 0.0]))
    y_axis_point_mm: np.ndarray = field(default_factory=lambda: np.array([0.0, 1.0]))

    def __post_init__(self):
        self.origin_mm = np.asarray(self.origin_mm, dtype=float)
        self.x_axis_point_mm = np.asarray(self.x_axis_point_mm, dtype=float)
        self.y_axis_point_mm = np.asarray(self.y_axis_point_mm, dtype=float)

        vx = self.x_axis_point_mm - self.origin_mm
        vy = self.y_axis_point_mm - self.origin_mm
        self._unit_x = vx / np.linalg.norm(vx)
        self._unit_y = vy / np.linalg.norm(vy)
        # 兩軸不假設互相垂直(實測角袋位置通常不會剛好90度),
        # 用矩陣求逆做仿射轉換, 而不是直接內積投影(那只有正交基底才精確)。
        self._basis = np.column_stack([self._unit_x, self._unit_y])
        self._basis_inv = np.linalg.inv(self._basis)

    @classmethod
    def from_arm_yaml_dict(cls, data: dict, origin_key: str, x_axis_key: str, y_axis_key: str) -> "ArmTableFrame":
        """從 arm.yaml 讀出的 dict 建立座標系, 角袋 key 名稱由外部指定。

        不寫死 pot0~pot3 這種 key 名, 因為新桌校準完之後, 對應哪個角袋
        當 origin/x軸/y軸參考點可能跟舊桌不同, 由呼叫端決定。
        """
        return cls(
            origin_mm=np.array(data[origin_key][0:2], dtype=float),
            x_axis_point_mm=np.array(data[x_axis_key][0:2], dtype=float),
            y_axis_point_mm=np.array(data[y_axis_key][0:2], dtype=float),
        )

    def arm_mm_to_pooltool_m(self, xy_mm) -> np.ndarray:
        xy_mm = np.asarray(xy_mm, dtype=float)
        rel_mm = xy_mm - self.origin_mm
        return (self._basis_inv @ rel_mm) / MM_PER_M

    def pooltool_m_to_arm_mm(self, xy_m) -> np.ndarray:
        xy_m = np.asarray(xy_m, dtype=float)
        xy_mm = xy_m * MM_PER_M
        return self.origin_mm + xy_mm[0] * self._unit_x + xy_mm[1] * self._unit_y


if __name__ == "__main__":
    # 用 placeholder 座標系(手臂座標=PoolTool座標*1000, 沒有旋轉/平移)
    # 驗證轉換邏輯本身正確, 不代表真實校準值。
    frame = ArmTableFrame()

    pt_xy_m = np.array([0.2, 0.7])
    arm_xy_mm = frame.pooltool_m_to_arm_mm(pt_xy_m)
    back_to_pt = frame.arm_mm_to_pooltool_m(arm_xy_mm)

    print("PoolTool (m):", pt_xy_m)
    print("-> 手臂座標 (mm):", arm_xy_mm)
    print("-> 轉回 PoolTool (m):", back_to_pt)
    assert np.allclose(pt_xy_m, back_to_pt)
