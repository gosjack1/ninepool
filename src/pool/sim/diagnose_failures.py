"""
跑 N 局 calibrate_weights.py 的同一套邏輯(find_best_route + PoolTool 模擬),
但開啟 failure logging, 產出三個同時間戳的檔案:

  results_<timestamp>.jsonl   每局一行, 完整原始資料(初始球位、選路分項、
                               預測/實際落點、失敗分類...)
  summary_<timestamp>.md      人類可讀的診斷報告(一句話結論 + 統計表 +
                               自動判讀規則)
  summary_<timestamp>.csv     跟 jsonl 同樣的資料攤平成表格, 給 pandas/Excel 用

這個腳本完全不碰 evaluate_weights()/make_objective()(Optuna 用的路徑),
只是另外呼叫 play_one_layout(..., enable_failure_log=True) 迴圈, 所以
校準時的效能不受影響。

用法:
    python3 diagnose_failures.py --n-layouts 20
    python3 diagnose_failures.py --n-layouts 200 --weights-yaml strategy_weights.yaml
"""

import argparse
from datetime import datetime, timezone
from pathlib import Path

import yaml

import calibrate_weights as cw
import failure_log
import nine_ball_strat as nbs


def load_weights(weights_yaml: Path | None) -> dict:
    if weights_yaml is None:
        return dict(
            angle_weight=nbs.DEFAULT_ANGLE_WEIGHT,
            dist_weight=nbs.DEFAULT_DIST_WEIGHT,
            n_weight=nbs.DEFAULT_N_WEIGHT,
            score_offset=nbs.DEFAULT_SCORE_OFFSET,
        )
    data = yaml.safe_load(weights_yaml.read_text())
    return dict(
        angle_weight=data.get("angle_weight", nbs.DEFAULT_ANGLE_WEIGHT),
        dist_weight=data.get("dist_weight", nbs.DEFAULT_DIST_WEIGHT),
        n_weight=data.get("n_weight", nbs.DEFAULT_N_WEIGHT),
        score_offset=data.get("score_offset", nbs.DEFAULT_SCORE_OFFSET),
    )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--n-layouts", type=int, default=20)
    parser.add_argument("--seed", type=int, default=0)
    parser.add_argument("--v0", type=float, default=2.5)
    parser.add_argument(
        "--weights-yaml", type=Path, default=None,
        help="不指定的話用 nine_ball_strat.py 裡的 DEFAULT_* 常數(baseline 權重)",
    )
    parser.add_argument(
        "--out-dir", type=Path, default=Path(__file__).with_name("logs"),
        help="三個輸出檔案存哪裡, 預設 sim/logs/",
    )
    args = parser.parse_args()

    weights = load_weights(args.weights_yaml)
    print(f"weights: {weights}")
    print(f"跑 {args.n_layouts} 局, v0={args.v0}, seed 從 {args.seed} 開始...")

    records = []
    for i in range(args.n_layouts):
        record = cw.play_one_layout(weights, seed=args.seed + i, v0=args.v0, enable_failure_log=True)
        records.append(record)

    timestamp = datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%SZ")
    jsonl_path, md_path, csv_path = failure_log.write_outputs(records, args.out_dir, timestamp)

    print(f"\n寫出:\n  {jsonl_path}\n  {md_path}\n  {csv_path}\n")
    print(md_path.read_text(encoding="utf-8"))


if __name__ == "__main__":
    main()