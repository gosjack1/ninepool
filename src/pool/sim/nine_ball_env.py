"""
NineBallEnv: PoolTool 物理模擬的 Gym 風格環境

reset()/step() 介面模仿 gymnasium.Env(回傳值 shape 一致), 但不強制依賴
gymnasium 套件 —— 之後真的要接 RL 訓練(stable-baselines3 之類)時, 包一層
gymnasium.Env 轉接就好, 不用改這裡的核心邏輯。

動作是打感應桿(Cue)的五個自由度: V0(桿速)、phi(方位角)、theta(桿仰角)、
a/b(左右/高低塞), 對應 pooltool 的 Cue.set_state()。

合法球/犯規/進球/勝負判定直接用 pooltool 內建的 NineBall ruleset
(pt.get_ruleset(pt.GameType.NINEBALL)), 不重新發明球規邏輯 —— pooltool 自己的
ruleset 引擎已經處理了 call-shot、犯規判定、respot 等細節。

⚠️ 目前只支援單一 agent 練習模式(不是雙人對打): 一桿結束(不管進球/犯規/
換手)就視為 episode 結束, 不會真的模擬"對手上場"。之後如果要練習防守或
雙人對局策略, next_shot_constraints 的球權轉換邏輯需要再擴充。

⚠️ reward function 是 placeholder, 對應交接文件待辦事項:
"跑10~20次隨機layout驗證 reward function(foul判斷、進球判斷)邏輯對不對"
——先把 obs/action/reward 的資料流接通, 權重之後再調。
"""

from dataclasses import dataclass
from typing import Dict, Optional, Tuple

import numpy as np
import pooltool as pt
from pooltool.objects import PocketTableSpecs

# 新桌實測規格(見 test_my_table.py, 已確認不用再改)
DEFAULT_TABLE_SPECS = PocketTableSpecs(
    l=1.120, w=0.550,
    cushion_width=0.0288, cushion_height=0.02432,
    corner_pocket_width=0.065, corner_pocket_depth=0.0237,
    corner_pocket_radius=0.0352, corner_jaw_radius=0.0119,
    side_pocket_width=0.080, side_pocket_depth=0.0389,
    side_pocket_radius=0.0366, side_jaw_radius=0.0045,
)
BALL_RADIUS_M = 0.019  # 38mm 直徑, 商品標示
CUE_BALL_ID = "cue"


@dataclass
class CueAction:
    """對應 pooltool Cue.set_state() 的五個自由度"""

    V0: float             # 桿速 (m/s)
    phi: float             # 方位角 (度)
    theta: float = 0.0     # 桿仰角 (度), 0 = 水平打
    a: float = 0.0         # 左右塞, 相對球半徑比例 (-1 ~ 1)
    b: float = 0.0         # 高低塞, 相對球半徑比例 (-1 ~ 1)


class NineBallEnv:
    """PoolTool 九球物理模擬環境, Gym-style reset()/step()。"""

    def __init__(
        self,
        table_specs: PocketTableSpecs = DEFAULT_TABLE_SPECS,
        ball_radius_m: float = BALL_RADIUS_M,
    ):
        self.table_specs = table_specs
        self.table = pt.Table.from_table_specs(table_specs)
        self.ball_radius_m = ball_radius_m

        self.shot: Optional[pt.System] = None
        self.ruleset = None

    def reset(
        self, *, seed: Optional[int] = None, randomize: bool = True
    ) -> Tuple[Dict[str, np.ndarray], dict]:
        if seed is not None:
            np.random.seed(seed)

        balls = pt.get_rack(
            pt.GameType.NINEBALL,
            self.table,
            ball_params=pt.BallParams(R=self.ball_radius_m),
        )
        cue = pt.Cue(cue_ball_id=CUE_BALL_ID)
        self.shot = pt.System(table=self.table, balls=balls, cue=cue)

        if randomize:
            if not self.shot.randomize_positions():
                # niter(預設100次)用完還是有重疊, 保留開球排列(rack)當 fallback,
                # 不拋例外 —— 之後如果常常發生, niter 要調大。
                pass

        ruleset_cls = pt.get_ruleset(pt.GameType.NINEBALL)
        self.ruleset = ruleset_cls(players=[pt.Player("agent")])

        return self._get_obs(), {}

    def step(
        self, action: CueAction
    ) -> Tuple[Dict[str, np.ndarray], float, bool, bool, dict]:
        if self.shot is None or self.ruleset is None:
            raise RuntimeError("call reset() before step()")

        self.shot.cue.set_state(
            V0=action.V0,
            phi=action.phi,
            theta=action.theta,
            a=action.a,
            b=action.b,
            cue_ball_id=CUE_BALL_ID,
        )
        pt.simulate(self.shot, inplace=True)
        self.ruleset.process_and_advance(self.shot)

        info = self.ruleset.shot_info
        reward = self._compute_reward(info)
        terminated = info.game_over or info.turn_over
        truncated = False

        return self._get_obs(), reward, terminated, truncated, {"shot_info": info}

    def _get_obs(self) -> Dict[str, np.ndarray]:
        """回傳桌上每顆球的 (x, y), 單位公尺, PoolTool 桌角原點座標系。

        被袋進的球會消失, 因為 pooltool 進球後直接從 shot.balls 移除。
        """
        return {
            ball_id: ball.state.rvw[0][:2].copy()
            for ball_id, ball in self.shot.balls.items()
        }

    def _compute_reward(self, info) -> float:
        """placeholder reward, 待用隨機layout跑過驗證後再調權重/細節。

        目前規則:
          - 犯規(shot 不合法): -1
          - 合法且沒換手(通常代表進球成功、可以繼續打): +1
          - 整局結束且有贏家: +10
          - 其餘(合法但沒進球, 換手): 0
        """
        if info.game_over:
            return 10.0 if info.winner is not None else 0.0
        if not info.legal:
            return -1.0
        if not info.turn_over:
            return 1.0
        return 0.0


if __name__ == "__main__":
    env = NineBallEnv()
    obs, _ = env.reset(seed=0)
    print("初始球位置 (m):", {k: v.tolist() for k, v in obs.items()})

    # smoke test: 瞄準 1號球打一桿, 確認資料流(reset->step->obs/reward/info)不會爆
    phi = pt.aim.at_ball(env.shot, "1")
    obs, reward, terminated, truncated, info = env.step(CueAction(V0=2.5, phi=phi))
    shot_info = info["shot_info"]
    print(
        f"reward={reward} terminated={terminated} "
        f"legal={shot_info.legal} reason={shot_info.reason!r} "
        f"turn_over={shot_info.turn_over} game_over={shot_info.game_over}"
    )
    print("剩餘球位置 (m):", {k: v.tolist() for k, v in obs.items()})
