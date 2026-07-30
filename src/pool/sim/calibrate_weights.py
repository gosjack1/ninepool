"""
用 Optuna 對 nine_ball_strat.py 的評分權重(angle_weight/dist_weight/n_weight)做搜索,
PoolTool 物理模擬當 fitness function 的驗證器(擊球是否真的合法進袋)。

跟交接文件的定位一致: PoolTool 負責「這個權重選出來的路線, 物理上真的會進嗎」,
不是重新訓練 policy, 只是幫 nine_ball_strat.py 裡手調的常數找更好的值。

場景: 母球 + 1號球(合法目標球) + 2號球(可能是障礙球, 也可能被拿來借打)。
對桌上 6 個袋口分別算「直球」(n=0)跟「借2號球打(kiss-ball, n=1)」的候選路線分數,
邏輯是照抄 nine_ball_strat.main() 的判斷順序(角度篩選 -> cue-target 路徑是否被擋 ->
target-pocket 路徑是否被擋 -> 0顆擋算直球, 1顆擋算 kiss-ball, 2顆以上跳過這個袋口),
確保跟正式的策略引擎行為一致, 而不是自己另外發明一套判斷。全部候選(6個袋口 x
最多2種路線)取分數最高的一個, 實際在 PoolTool 打一桿, 檢查對應的球有沒有真的
合法進到選中的袋口。

⚠️ 已知簡化, 之後要擴充：
  1. 不含反彈球(reflected_route)。原本 main() 在「target-pocket 路徑被 2 顆以上
     球擋住」時會 fallback 去試反彈路線, 這裡直接跳過那個袋口候選, 不計分。
  2. 桿速 V0 是固定常數(--v0), 沒有一起被 Optuna 優化 —— 這次只調角度/距離/
     路線複雜度的權重, 力道校準留給交接文件裡「solenoid 驅動參數 -> V0
     校準表」那個獨立待辦。combo(kiss-ball)路線因為要打三段距離(母球->1號->
     2號->袋口), 固定 V0 對它明顯偏保守, 進球率會遠低於直球, 這是預期中的
     物理限制, 不是校準邏輯錯誤(已經實際跑過, 用 events 確認過 cue->1->2
     的碰撞順序完全照幾何算出來的方向發生, 只是最後一段常常擦到庫邊沒進袋、
     或母球借力後自己洗袋 —— 這正是 kiss-ball 這種路線在真實撞球裡也比較難、
     風險比較高的原因, n_weight 的角色就是在權衡這種風險)。
  3. ⚠️ 沿用 nine_ball_strat.py main() 自己的一個限制: kiss-ball 分支重新算出
     的母球瞄準向量(瞄準 1 號球的新 ghost point, 不是直球瞄準點)並「沒有」
     重新檢查這條新路徑上有沒有球擋住 —— 這是原始 main() 就有的行為, 這裡
     照原樣搬過來, 不是我們新引入的 bug。
  4. [已修正] simple_route() 裡的 angle 曾經退回用 math.acos() 算「弧度」,
     跟 reflected_route() 用 angle_between_vector() 算「角度」不一致, 導致
     同一個 angle_weight 常數在兩邊量級差 ~57倍(180/π)。已把 simple_route()
     的 angle0/angle1/angle2 全部改回呼叫 angle_between_vector(), 現在兩邊
     單位一致, 校準出來的 angle_weight 可以共用。

用法:
    python3 calibrate_weights.py --n-trials 30 --n-layouts 30
    (跑完會印出 direct/combo 分開的成功率, 並存一份 YAML 到 --output, 預設存在
    這個 sim/ 資料夾裡, 不會自動覆蓋 hiwin_control/strategy_weights.yaml
    ——校準結果先自己看過覺得合理, 再手動複製過去)
"""

import argparse
import math
import sys
from collections import Counter
from pathlib import Path

import numpy as np
import optuna
import pooltool as pt
import yaml

_HIWIN_PKG_DIR = Path(__file__).resolve().parents[2] / "hiwin_control" / "hiwin_control"
sys.path.insert(0, str(_HIWIN_PKG_DIR))
sys.path.insert(0, str(_HIWIN_PKG_DIR.parent))
import matplotlib

matplotlib.use("Agg")  # headless, 避免每次 simple_route/main 相關的 plt 呼叫嘗試開視窗
import nine_ball_strat as nbs  # noqa: E402  (要先插入 sys.path 才能 import)

from nine_ball_env import BALL_RADIUS_M, DEFAULT_TABLE_SPECS  # noqa: E402
import failure_log  # noqa: E402  (只有 enable_failure_log=True 時才會被用到)

CUE_BALL_ID = "cue"
TARGET_BALL_ID = "1"
OBSTACLE_BALL_ID = "2"
ANGLE_GATE_DEG = 80.0  # 跟 nine_ball_strat.main() 裡的角度篩選門檻一致


def find_best_route(shot: pt.System, weights: dict):
    """對 6 個袋口分別算直球/kiss-ball 候選分數, 回傳分數最高的那個。

    回傳 dict(kind, pocket_id, cue_vx, cue_vy, sink_ball_id, first_contact_ball_id,
    score_breakdown, predicted_landing_mm, score) 或 None(所有袋口都沒有合法候選
    路線)。sink_ball_id 是這一桿實際上該進袋的球: direct 是 1號球本身, combo
    是被借打的 2號球; first_contact_ball_id 是母球該先碰到的球, 目前不管
    direct/combo 都一定是 1號球(母球一律先瞄準1號球的 ghost point)。
    score_breakdown 直接來自 nbs.simple_route(return_breakdown=True) 當下算
    score 用的那三個分項(angle_score/dist_score/n_score), 不是事後重算, 加總
    保證等於 score —— 不要再另外寫一份公式重算, 上次(decompose_score)就是
    這樣搞出跟實際分數對不上的 bug。
    """
    cue_xy_mm = shot.balls[CUE_BALL_ID].state.rvw[0][:2] * 1000
    target_xy_mm = shot.balls[TARGET_BALL_ID].state.rvw[0][:2] * 1000
    obstacle_xy_mm = shot.balls[OBSTACLE_BALL_ID].state.rvw[0][:2] * 1000
    # index 0 一定是目標球(1號), 跟 nine_ball_strat 的 check_ball_in_way(i!=0 跳過自己)慣例一致
    objectballx = [target_xy_mm[0], obstacle_xy_mm[0]]
    objectbally = [target_xy_mm[1], obstacle_xy_mm[1]]

    candidates = []  # (score, kind, pocket_id, cue_vx, cue_vy, sink_ball_id, score_breakdown, pocket_xy_mm)

    for pocket_id, pocket in shot.table.pockets.items():
        pocket_xy_mm = pocket.center[:2] * 1000
        try:
            _, target_vx, target_vy = nbs.disandvec(
                pocket_xy_mm[0], pocket_xy_mm[1], target_xy_mm[0], target_xy_mm[1]
            )
            target_hit_x, target_hit_y = nbs.findhitpoint(target_xy_mm[0], target_xy_mm[1], target_vx, target_vy)
            _, cue_vx, cue_vy = nbs.disandvec(target_hit_x, target_hit_y, cue_xy_mm[0], cue_xy_mm[1])

            angle = nbs.angle_between_vector([target_vx, target_vy], [cue_vx, cue_vy])
            if angle >= ANGLE_GATE_DEG:
                continue

            # cue -> target 路徑有沒有被擋(用直球瞄準向量)
            p1, p2, p3, p4 = nbs.vector_mask(cue_xy_mm[0], cue_xy_mm[1], cue_vx, cue_vy)
            n_obs_cue, _ = nbs.check_ball_in_way(p1, p2, p3, p4, objectballx, objectbally)
            if n_obs_cue != 0:
                continue

            # target -> pocket 路徑有沒有被擋
            p1, p2, p3, p4 = nbs.vector_mask(target_xy_mm[0], target_xy_mm[1], target_vx, target_vy)
            n_obs_target, blocker_indices = nbs.check_ball_in_way(p1, p2, p3, p4, objectballx, objectbally)

            if n_obs_target == 0:
                score, _, _, breakdown = nbs.simple_route(
                    cue=[cue_xy_mm[0], cue_xy_mm[1]],
                    cuetoivector=[cue_vx, cue_vy],
                    toholevector=[target_vx, target_vy],
                    n=0,
                    return_breakdown=True,
                    **weights,
                )
                candidates.append(
                    (score, "direct", pocket_id, cue_vx, cue_vy, TARGET_BALL_ID, breakdown, pocket_xy_mm)
                )

            elif n_obs_target == 1:
                # kiss-ball: 借 2 號球(唯一擋到的那顆)打進袋口
                bidx = blocker_indices[0]
                bx, by = objectballx[bidx], objectbally[bidx]
                _, kiss_aim_vx, kiss_aim_vy = nbs.disandvec(pocket_xy_mm[0], pocket_xy_mm[1], bx, by)
                kiss_hit_x, kiss_hit_y = nbs.findhitpoint(bx, by, kiss_aim_vx, kiss_aim_vy)
                _, target_kiss_vx, target_kiss_vy = nbs.disandvec(
                    kiss_hit_x, kiss_hit_y, target_xy_mm[0], target_xy_mm[1]
                )
                target_kiss_hit_x, target_kiss_hit_y = nbs.findhitpoint(
                    target_xy_mm[0], target_xy_mm[1], target_kiss_vx, target_kiss_vy
                )
                _, cue_kiss_vx, cue_kiss_vy = nbs.disandvec(
                    target_kiss_hit_x, target_kiss_hit_y, cue_xy_mm[0], cue_xy_mm[1]
                )

                cue_target_kiss_angle = nbs.angle_between_vector(
                    [cue_kiss_vx, cue_kiss_vy], [target_kiss_vx, target_kiss_vy]
                )
                target_kiss_aim_angle = nbs.angle_between_vector(
                    [target_kiss_vx, target_kiss_vy], [kiss_aim_vx, kiss_aim_vy]
                )
                if cue_target_kiss_angle >= ANGLE_GATE_DEG or target_kiss_aim_angle >= ANGLE_GATE_DEG:
                    continue

                score, _, _, breakdown = nbs.simple_route(
                    cue=[cue_xy_mm[0], cue_xy_mm[1]],
                    cuetoivector=[cue_kiss_vx, cue_kiss_vy],
                    itok2vector=[target_kiss_vx, target_kiss_vy],
                    toholevector=[kiss_aim_vx, kiss_aim_vy],
                    n=1,
                    return_breakdown=True,
                    **weights,
                )
                candidates.append(
                    (score, "combo", pocket_id, cue_kiss_vx, cue_kiss_vy, OBSTACLE_BALL_ID, breakdown, pocket_xy_mm)
                )

            # n_obs_target >= 2: 太多球擋住(對應原本 main() 的 reflected route fallback),
            # 這版還沒接反彈路線, 這個袋口候選直接跳過。
        except (ValueError, ZeroDivisionError):
            # 極端幾何(向量長度剛好 0 等)導致 acos/除法出界, 跳過這個袋口候選
            continue

    if not candidates:
        return None

    (score, kind, pocket_id, cue_vx, cue_vy, sink_ball_id,
     breakdown, pocket_xy_mm) = max(candidates, key=lambda c: c[0])
    return dict(
        kind=kind,
        pocket_id=pocket_id,
        cue_vx=cue_vx,
        cue_vy=cue_vy,
        sink_ball_id=sink_ball_id,
        first_contact_ball_id=TARGET_BALL_ID,  # direct/combo 都一律先瞄準1號球
        score_breakdown=breakdown,
        predicted_landing_mm=(float(pocket_xy_mm[0]), float(pocket_xy_mm[1])),
        score=score,
    )


def play_one_layout(weights: dict, seed: int, v0: float, enable_failure_log: bool = False):
    """建一組隨機母球+1號+2號球局面, 用給定權重選路線, 實際在 PoolTool 打一桿。

    enable_failure_log=False(預設, Optuna 大量 rollout 用這條路徑): 回傳
    (kind, success) 或 None(找不到候選路線), 跟原本行為完全一樣, 不額外算
    任何東西, 不影響校準效能。

    enable_failure_log=True(diagnose_failures.py 用這條路徑): 一律回傳一筆
    完整的 dict record(見 failure_log.build_episode_record/build_skipped_record),
    包含找不到候選路線的 layout 也會回傳(記成 outcome='skipped', 不是 None),
    確保「無解局面」不會被 continue 丟掉。
    """
    np.random.seed(seed)
    table = pt.Table.from_table_specs(DEFAULT_TABLE_SPECS)
    balls = {
        CUE_BALL_ID: pt.Ball.create(CUE_BALL_ID, R=BALL_RADIUS_M),
        TARGET_BALL_ID: pt.Ball.create(TARGET_BALL_ID, R=BALL_RADIUS_M),
        OBSTACLE_BALL_ID: pt.Ball.create(OBSTACLE_BALL_ID, R=BALL_RADIUS_M),
    }
    shot = pt.System(table=table, balls=balls, cue=pt.Cue(cue_ball_id=CUE_BALL_ID))
    shot.randomize_positions()

    initial_state = None
    if enable_failure_log:
        initial_state = {
            bid: [float(b.state.rvw[0][0] * 1000), float(b.state.rvw[0][1] * 1000)]
            for bid, b in shot.balls.items()
        }

    route = find_best_route(shot, weights)
    if route is None:
        if not enable_failure_log:
            return None
        return failure_log.build_skipped_record(episode_id=seed, initial_state=initial_state, v0=v0)

    phi = math.degrees(math.atan2(route["cue_vy"], route["cue_vx"])) % 360
    shot.cue.set_state(V0=v0, phi=phi, cue_ball_id=CUE_BALL_ID)
    pt.simulate(shot, inplace=True)

    # ⚠️ 這個 pooltool 版本(0.3.3)的 pt.simulate() 不會把進袋的球從 shot.balls 移除
    # (那是 ruleset.process_and_advance()/respot_balls() 才會做的事, 這裡完全沒用
    # ruleset)。進袋的球會留在 shot.balls 裡, 但座標會被移到袋口位置, 並登記進
    # pocket.contains。所以「洗袋」要查 pocket.contains, 不能用 `not in shot.balls`
    # 判斷 —— 後者永遠是 False, 之前這裡是這樣寫的, 導致 cue_scratched 永遠算成
    # False, foul_cue_potted 這個 failure_type 實際上從來沒被分類到過, 且
    # evaluate_weights()/Optuna 算出來的成功率一直沒把「球進袋但母球也洗袋」算
    # 成失敗(這件事一路影響到目前為止所有校準結果, 見這次驗收時用 seed=14 對到
    # 的實際案例)。
    cue_scratched = any(CUE_BALL_ID in pocket.contains for pocket in table.pockets.values())
    sunk_correctly = route["sink_ball_id"] in table.pockets[route["pocket_id"]].contains

    if not enable_failure_log:
        return route["kind"], (sunk_correctly and not cue_scratched)

    pockets_after = {pid: set(pocket.contains) for pid, pocket in table.pockets.items()}
    # ⚠️ 之前這裡直接讀 shot.balls[sink_ball_id] 的座標當「實際落點」, 但進袋的球
    # 這個座標會被 pooltool 直接搬到袋口中心(見上面 cue_scratched 那條註解),
    # 導致成功局的 landing_error 恆等於 0 —— 那只是「有沒有進對袋」的同義反覆,
    # 不是真的執行精度。改用 BALL_POCKET 事件的 agent.initial(進袋那一刻、被搬
    # 到袋口中心"之前"的真實位置)當實際落點; 沒進袋的話沿用原本邏輯讀
    # shot.balls 目前(靜止後)的座標。
    actual_target_landing = None
    for e in shot.events:
        if e.event_type.name == "BALL_POCKET":
            for a in e.agents:
                if a.id == route["sink_ball_id"] and a.initial is not None:
                    pre_pot_xy = a.initial.state.rvw[0][:2] * 1000
                    actual_target_landing = (float(pre_pot_xy[0]), float(pre_pot_xy[1]))
                    break
        if actual_target_landing is not None:
            break
    if actual_target_landing is None:
        xy = shot.balls[route["sink_ball_id"]].state.rvw[0][:2] * 1000
        actual_target_landing = (float(xy[0]), float(xy[1]))

    return failure_log.build_episode_record(
        episode_id=seed,
        initial_state=initial_state,
        route=route,
        v0=v0,
        events=shot.events,
        cue_id=CUE_BALL_ID,
        pockets_after=pockets_after,
        actual_target_landing=actual_target_landing,
        cue_scratched=cue_scratched,
    )


def evaluate_weights(weights: dict, n_layouts: int, base_seed: int, v0: float) -> dict:
    """回傳整體/direct/combo 各自的成功率跟樣本數, 跳過沒有候選路線的 layout。"""
    considered = Counter()
    successes = Counter()
    for i in range(n_layouts):
        result = play_one_layout(weights, seed=base_seed + i, v0=v0)
        if result is None:
            continue
        kind, success = result
        considered[kind] += 1
        considered["overall"] += 1
        if success:
            successes[kind] += 1
            successes["overall"] += 1

    return {
        "overall_rate": successes["overall"] / considered["overall"] if considered["overall"] else 0.0,
        "direct_rate": successes["direct"] / considered["direct"] if considered["direct"] else None,
        "combo_rate": successes["combo"] / considered["combo"] if considered["combo"] else None,
        "n_direct": considered["direct"],
        "n_combo": considered["combo"],
    }


def make_objective(n_layouts: int, base_seed: int, v0: float):
    def objective(trial: optuna.Trial) -> float:
        weights = dict(
            angle_weight=trial.suggest_float("angle_weight", 100.0, 3000.0),
            dist_weight=trial.suggest_float("dist_weight", 0.1, 20.0),
            # n_weight 現在有真正的效果了: n=1(combo) 分支會被實際評分/選中,
            # 這個權重決定候選挑選時要多不情願去選风险較高的 kiss-ball 路線。
            n_weight=trial.suggest_float("n_weight", 100.0, 3000.0),
        )
        return evaluate_weights(weights, n_layouts=n_layouts, base_seed=base_seed, v0=v0)["overall_rate"]

    return objective


def format_result(label: str, result: dict) -> str:
    direct = "n/a" if result["direct_rate"] is None else f"{result['direct_rate']:.3f}"
    combo = "n/a" if result["combo_rate"] is None else f"{result['combo_rate']:.3f}"
    return (
        f"{label}: overall={result['overall_rate']:.3f}  "
        f"direct={direct}(n={result['n_direct']})  combo={combo}(n={result['n_combo']})"
    )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--n-trials", type=int, default=30)
    parser.add_argument("--n-layouts", type=int, default=30, help="每個 trial 用幾組隨機局面評分")
    parser.add_argument("--seed", type=int, default=0, help="random layout 的起始 seed")
    parser.add_argument("--v0", type=float, default=2.5, help="固定桿速 (m/s), 這版還沒一起優化")
    parser.add_argument(
        "--output",
        type=Path,
        default=Path(__file__).with_name("strategy_weights.yaml"),
        help="校準結果存哪裡(預設存在 sim/ 資料夾, 不動 hiwin_control 裡的正式檔案)",
    )
    args = parser.parse_args()

    baseline = dict(
        angle_weight=nbs.DEFAULT_ANGLE_WEIGHT,
        dist_weight=nbs.DEFAULT_DIST_WEIGHT,
        n_weight=nbs.DEFAULT_N_WEIGHT,
    )
    baseline_result = evaluate_weights(baseline, n_layouts=args.n_layouts, base_seed=args.seed, v0=args.v0)
    print(format_result("baseline(原本寫死的權重)", baseline_result))
    print(f"  {baseline}")

    study = optuna.create_study(direction="maximize")
    study.optimize(
        make_objective(n_layouts=args.n_layouts, base_seed=args.seed, v0=args.v0),
        n_trials=args.n_trials,
    )

    best_result = evaluate_weights(study.best_params, n_layouts=args.n_layouts, base_seed=args.seed, v0=args.v0)
    print()
    print(format_result("最佳權重", best_result))
    print(f"  {study.best_params}")

    with open(args.output, "w") as f:
        yaml.safe_dump(
            {
                "angle_weight": study.best_params["angle_weight"],
                "dist_weight": study.best_params["dist_weight"],
                "n_weight": study.best_params["n_weight"],
                "score_offset": nbs.DEFAULT_SCORE_OFFSET,  # 這次沒優化, 沿用原值
                "v0_fixed_during_calibration": args.v0,
                "baseline_overall_success_rate": baseline_result["overall_rate"],
                "best_overall_success_rate": best_result["overall_rate"],
            },
            f,
            allow_unicode=True,
        )
    print(f"\n已存到 {args.output}, 看過覺得合理再手動複製/合併到 "
          f"src/hiwin_control/hiwin_control/strategy_weights.yaml")


if __name__ == "__main__":
    main()