#!/usr/bin/env python3
"""
自碰撞可行域掃描 —— 第一版(尚未接 IK,直接掃六軸角度)

用法:
    python3 self_collision_scan.py

輸出:
    feasibility_map.csv  —— 每一列是一組六軸角度 + 是否自撞

注意:
    - J2 的角度,這裡輸入/輸出的都是「控制器回報角度」(theta2'),
      內部會自動做 theta2_physical = theta2' - 90 再餵給 MuJoCo。
      不要自己在外部先減 90,函式內部已經處理。
    - 目前末端幾何是「近似版」(見 ra605_full.xml 裡的說明),
      roll 角度未鎖定,掃描結果暫時僅供流程測試用,不代表真實自撞結論。
"""
import mujoco
import numpy as np
import itertools
import csv
import time
from pathlib import Path

# 相對於本檔案的位置定位,不管從哪個目錄執行都能正確找到檔案
SCRIPT_DIR = Path(__file__).resolve().parent
MODEL_PATH = str(SCRIPT_DIR / "ra605_full.xml")
OUTPUT_CSV = str(SCRIPT_DIR / "feasibility_map.csv")

# 跟手臂本體、地板 __以外__ 才算數的碰撞(排除清單已經在 XML 的 <contact><exclude> 處理過
# 相鄰關節了;這裡再排除 floor,因為 floor 只是視覺輔助,不是真實碰撞對象)
IGNORE_GEOMS = {"floor"}

class SelfCollisionChecker:
    def __init__(self, model_path=MODEL_PATH):
        self.model = mujoco.MjModel.from_xml_path(model_path)
        self.data = mujoco.MjData(self.model)
        self.joint_names = ["J1", "J2", "J3", "J4", "J5", "J6"]
        self.qpos_addr = [self.model.jnt_qposadr[self.model.joint(n).id] for n in self.joint_names]

    def check(self, controller_angles_deg):
        """
        controller_angles_deg: [J1,J2,J3,J4,J5,J6] 六個角度(度),
                                J2 是「控制器回報角度」,函式內部自動換算。
        回傳: (collided: bool, contact_pairs: list of (geomA, geomB, dist))
        """
        physical = list(controller_angles_deg)
        physical[1] = physical[1] - 90.0   # J2 換算,DH 表 θ2 = θ2' - 90

        for addr, deg in zip(self.qpos_addr, physical):
            self.data.qpos[addr] = np.radians(deg)
        mujoco.mj_forward(self.model, self.data)

        contacts = []
        for i in range(self.data.ncon):
            c = self.data.contact[i]
            g1 = self.model.geom(c.geom1).name
            g2 = self.model.geom(c.geom2).name
            if g1 in IGNORE_GEOMS or g2 in IGNORE_GEOMS:
                continue
            contacts.append((g1, g2, round(float(c.dist), 3)))

        return (len(contacts) > 0), contacts


def main():
    checker = SelfCollisionChecker()

    # ---- 第一版掃描範圍:先用粗網格、小範圍測試流程,不追求完整覆蓋 ----
    # 之後接 IK 之後,這裡會改成「對每個候選 hitpoint+yaw 呼叫 IK 拿到這組角度」,
    # 而不是像現在這樣直接對六軸角度本身做網格掃描。
    j1_range = np.arange(-60, 61, 20)     # 度
    j2_range = np.arange(-60, 1, 20)      # 控制器角度(未減90)
    j3_range = np.arange(-30, 31, 30)
    j4_range = [0]     # 先固定,減少組合數
    j5_range = [0]
    j6_range = np.arange(-90, 91, 45)

    combos = list(itertools.product(j1_range, j2_range, j3_range, j4_range, j5_range, j6_range))
    print(f"共 {len(combos)} 組角度要測試")

    results = []
    t0 = time.time()
    n_collide = 0
    for angles in combos:
        collided, contacts = checker.check(angles)
        if collided:
            n_collide += 1
        results.append({
            "J1": angles[0], "J2": angles[1], "J3": angles[2],
            "J4": angles[3], "J5": angles[4], "J6": angles[5],
            "collided": int(collided),
            "contacts": ";".join(f"{a}-{b}({d})" for a,b,d in contacts) if contacts else ""
        })

    elapsed = time.time() - t0
    print(f"完成,耗時 {elapsed:.1f}s,平均每組 {elapsed/len(combos)*1000:.2f}ms")
    print(f"碰撞組數: {n_collide} / {len(combos)} ({n_collide/len(combos)*100:.1f}%)")

    out_path = OUTPUT_CSV
    with open(out_path, "w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=results[0].keys())
        writer.writeheader()
        writer.writerows(results)
    print(f"結果存到 {out_path}")

if __name__ == "__main__":
    main()
