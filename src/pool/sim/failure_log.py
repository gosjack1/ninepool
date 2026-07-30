"""
failure logging: 幫 calibrate_weights.py 的每一局(不論成敗)記錄結構化 log,
失敗原因直接從 PoolTool 模擬產生的事件序列判讀, 不用猜的。

跟 calibrate_weights.py 的關係: 那邊的 play_one_layout()/find_best_route() 在
enable_failure_log=True 時會呼叫這裡的函式組出一筆 record; Optuna 大量 rollout
時(enable_failure_log=False, 預設)完全不會呼叫到這個檔案裡的任何東西, 不影響
校準效能。

failure_type 分類邏輯(對照 diagnose_failures.py 產生的 summary_*.md 裡的表格):
  no_contact         母球完全沒碰到任何球
  wrong_ball_first   母球第一個碰到的不是這局該打的球(chosen_ball)
  foul_cue_potted    母球碰對球了, 但自己也洗袋(不論目標球有沒有進)
  potted_wrong_pocket 目標球有進袋, 但不是選定的那個袋口
  contact_no_pot     母球碰對球, 目標球沒進任何袋口
  other              以上都不符合的例外情況(理論上不該出現, 保底用)
成功局(目標球進了選定袋口且母球沒洗袋)的 failure_type 是 None。
"""

import csv
import json
import statistics
from pathlib import Path
from typing import Dict, List, Optional, Tuple

import numpy as np


def classify_outcome(
    events,
    cue_id: str,
    chosen_ball_id: str,
    intended_pocket_id: str,
    sink_ball_id: str,
    pockets_after: Dict[str, set],
    cue_scratched: bool,
) -> Tuple[str, Optional[str]]:
    """從事件序列 + 賽後袋口內容判讀這一局的 outcome/failure_type。

    events: pt.System.events(模擬後的事件序列, 依時間順序)
    pockets_after: {pocket_id: set(ball_id 有進這個袋口)}, 模擬後的快照
    回傳 (outcome, failure_type), outcome 是 'success'/'fail', 成功時 failure_type=None。
    """
    try:
        first_contact = None
        for e in events:
            if e.event_type.name == "BALL_BALL":
                ids = [a.id for a in e.agents]
                if cue_id in ids:
                    other = [i for i in ids if i != cue_id]
                    first_contact = other[0] if other else None
                    break

        if first_contact is None:
            return "fail", "no_contact"
        if first_contact != chosen_ball_id:
            return "fail", "wrong_ball_first"
        if cue_scratched:
            return "fail", "foul_cue_potted"
        if sink_ball_id in pockets_after.get(intended_pocket_id, set()):
            return "success", None
        for pid, contains in pockets_after.items():
            if pid != intended_pocket_id and sink_ball_id in contains:
                return "fail", "potted_wrong_pocket"
        return "fail", "contact_no_pot"
    except Exception:
        return "fail", "other"


def compute_landing_error(predicted_mm, actual_mm) -> Optional[float]:
    if predicted_mm is None or actual_mm is None:
        return None
    return float(((predicted_mm[0] - actual_mm[0]) ** 2 + (predicted_mm[1] - actual_mm[1]) ** 2) ** 0.5)


def build_skipped_record(episode_id, initial_state: dict, v0: float) -> dict:
    """find_best_route() 找不到任何候選路線的 layout —— 明確記一筆, 不要 continue 丟掉。"""
    return {
        "episode_id": episode_id,
        "initial_state": initial_state,
        "chosen_ball": None,
        "chosen_pocket": None,
        "route_kind": None,
        "sink_ball_id": None,
        "route_scores": None,
        "V0": None,
        "predicted_landing": None,
        "actual_target_landing": None,
        "landing_error": None,
        "outcome": "skipped",
        "failure_type": "skipped_no_route",
    }


def build_episode_record(
    episode_id,
    initial_state: dict,
    route: dict,
    v0: float,
    events,
    cue_id: str,
    pockets_after: Dict[str, set],
    actual_target_landing,
    cue_scratched: bool,
) -> dict:
    # route["score_breakdown"] 是 nine_ball_strat.simple_route(return_breakdown=True)
    # 算 score 當下順手記下來的三個分項, 不是這裡重算的 —— 不會再有分項加總跟
    # 實際分數對不上的問題(那是上一版 decompose_score() 自己重算公式造成的 bug,
    # 直接拿 simple_route 自己算的分項就沒有「兩份公式」這回事了)。
    scores = dict(route["score_breakdown"])

    outcome, failure_type = classify_outcome(
        events=events,
        cue_id=cue_id,
        chosen_ball_id=route["first_contact_ball_id"],
        intended_pocket_id=route["pocket_id"],
        sink_ball_id=route["sink_ball_id"],
        pockets_after=pockets_after,
        cue_scratched=cue_scratched,
    )

    predicted = route["predicted_landing_mm"]
    landing_error = compute_landing_error(predicted, actual_target_landing)

    return {
        "episode_id": episode_id,
        "initial_state": initial_state,
        "chosen_ball": route["first_contact_ball_id"],
        "chosen_pocket": route["pocket_id"],
        "route_kind": route["kind"],
        "sink_ball_id": route["sink_ball_id"],
        "route_scores": scores,
        "V0": v0,
        "predicted_landing": list(predicted),
        "actual_target_landing": list(actual_target_landing) if actual_target_landing else None,
        "landing_error": landing_error,
        "outcome": outcome,
        "failure_type": failure_type,
    }


# ---------------------------------------------------------------------------
# 輸出檔案: jsonl(完整原始資料) / csv(攤平給 pandas/Excel) / md(人類可讀報告)
# ---------------------------------------------------------------------------

_BALL_IDS_FOR_CSV = ["cue", "1", "2"]


def write_jsonl(records: List[dict], path: Path) -> None:
    with open(path, "w") as f:
        for r in records:
            f.write(json.dumps(r, ensure_ascii=False) + "\n")


def write_csv(records: List[dict], path: Path) -> None:
    fieldnames = (
        [f"{b}_x" for b in _BALL_IDS_FOR_CSV]
        + [f"{b}_y" for b in _BALL_IDS_FOR_CSV]
        + [
            "episode_id", "chosen_ball", "chosen_pocket", "route_kind", "sink_ball_id",
            "angle_score", "dist_score", "n_score", "V0",
            "predicted_landing_x", "predicted_landing_y",
            "actual_landing_x", "actual_landing_y",
            "landing_error", "outcome", "failure_type",
        ]
    )
    with open(path, "w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        for r in records:
            row = {"episode_id": r["episode_id"]}
            for b in _BALL_IDS_FOR_CSV:
                xy = r["initial_state"].get(b) if r["initial_state"] else None
                row[f"{b}_x"], row[f"{b}_y"] = (xy[0], xy[1]) if xy else (None, None)
            row["chosen_ball"] = r["chosen_ball"]
            row["chosen_pocket"] = r["chosen_pocket"]
            row["route_kind"] = r["route_kind"]
            row["sink_ball_id"] = r["sink_ball_id"]
            scores = r["route_scores"] or {}
            row["angle_score"] = scores.get("angle_score")
            row["dist_score"] = scores.get("dist_score")
            row["n_score"] = scores.get("n_score")
            row["V0"] = r["V0"]
            pl = r["predicted_landing"]
            row["predicted_landing_x"], row["predicted_landing_y"] = (pl[0], pl[1]) if pl else (None, None)
            al = r["actual_target_landing"]
            row["actual_landing_x"], row["actual_landing_y"] = (al[0], al[1]) if al else (None, None)
            row["landing_error"] = r["landing_error"]
            row["outcome"] = r["outcome"]
            row["failure_type"] = r["failure_type"]
            writer.writerow(row)


def _pct(part: int, whole: int) -> float:
    return 100.0 * part / whole if whole else 0.0


def render_summary_md(records: List[dict], timestamp: str) -> str:
    n_total = len(records)
    outcomes = [r["outcome"] for r in records]
    n_success = outcomes.count("success")
    n_fail = outcomes.count("fail")
    n_skipped = outcomes.count("skipped")
    n_considered = n_success + n_fail
    success_rate = _pct(n_success, n_considered) if n_considered else 0.0

    fail_records = [r for r in records if r["outcome"] == "fail"]
    fail_type_counts: Dict[str, int] = {}
    for r in fail_records:
        ft = r["failure_type"] or "other"
        fail_type_counts[ft] = fail_type_counts.get(ft, 0) + 1

    labels = {
        "contact_no_pot": "碰對球沒進袋 → 執行/力道",
        "wrong_ball_first": "先碰錯球 → 選球/選路",
        "no_contact": "沒碰到球 → 幾何/座標",
        "potted_wrong_pocket": "進錯袋 → 選路",
        "foul_cue_potted": "母球洗袋 → 力道/走位",
        "other": "",
    }

    landing_errors_all = [r["landing_error"] for r in records if r["landing_error"] is not None]
    landing_errors_success = [
        r["landing_error"] for r in records if r["outcome"] == "success" and r["landing_error"] is not None
    ]
    landing_errors_fail = [
        r["landing_error"] for r in records if r["outcome"] == "fail" and r["landing_error"] is not None
    ]

    def stats_block(values):
        if not values:
            return "（無資料）"
        return (
            f"- 中位數：{statistics.median(values):.1f} mm\n"
            f"- 平均：{statistics.mean(values):.1f} mm\n"
            f"- 90 百分位：{np.percentile(values, 90):.1f} mm\n"
            f"- 樣本數：{len(values)}"
        )

    # --- 自動判讀 ---
    findings = []
    top_failure_type = None
    top_failure_pct = 0.0
    if fail_type_counts:
        top_failure_type = max(fail_type_counts, key=fail_type_counts.get)
        top_failure_pct = _pct(fail_type_counts[top_failure_type], n_fail)

    fail_median = statistics.median(landing_errors_fail) if landing_errors_fail else None

    if top_failure_type == "contact_no_pot":
        if fail_median is not None and fail_median > 30:
            findings.append(f"瓶頸在力道方向/大小，建議改 V0（失敗局 landing_error 中位數 {fail_median:.1f}mm > 30mm）")
        elif fail_median is not None and fail_median < 15:
            findings.append(f"方向準，純力道大小問題，只調 V0 大小（失敗局 landing_error 中位數 {fail_median:.1f}mm < 15mm）")
    if top_failure_type in ("wrong_ball_first", "potted_wrong_pocket"):
        findings.append("瓶頸在選路，檢查評分公式")
    if top_failure_type == "no_contact":
        findings.append("瓶頸在幾何/座標，回查鬼球法")
    if n_total and _pct(n_skipped, n_total) > 30:
        findings.append(
            f"分母不乾淨（skipped_no_route 佔總抽樣 {_pct(n_skipped, n_total):.1f}%），"
            "find_best_route 的 80 度門檻可能太嚴，或很多局面本來無解"
        )

    if not findings:
        one_liner = "沒有觸發任何自動判讀規則（樣本太少或分佈平均），建議加大 n-layouts 再看。"
    elif top_failure_type:
        one_liner = (
            f"主要瓶頸是【{labels.get(top_failure_type, top_failure_type)}】："
            f"{top_failure_pct:.0f}% 的失敗是 {top_failure_type}"
            + (f"，落點誤差中位數 {fail_median:.1f}mm" if fail_median is not None else "")
            + f"。建議：{findings[0]}"
        )
    else:
        one_liner = findings[0]

    # --- 組 markdown ---
    lines = []
    lines.append(f"# 校準結果診斷報告  {timestamp}")
    lines.append("")
    lines.append("## 一句話結論")
    lines.append(one_liner)
    lines.append("")
    lines.append("## 樣本概況")
    lines.append(f"- 總抽樣局數：{n_total}")
    lines.append(f"- 成功：{n_success}（{_pct(n_success, n_total):.1f}%）")
    lines.append(f"- 失敗：{n_fail}（{_pct(n_fail, n_total):.1f}%）")
    lines.append(f"- 無解跳過（skipped_no_route）：{n_skipped}（佔總抽樣 {_pct(n_skipped, n_total):.1f}%）")
    lines.append(f"- 實際計入成功率分母：{n_total} - {n_skipped} = {n_considered}")
    lines.append(f"- 成功率（只算有解局面）：{n_success} / {n_considered} = {success_rate:.1f}%")
    lines.append("")
    lines.append("## 失敗類型分佈（只看 fail 的局）")
    lines.append("| failure_type | 局數 | 佔失敗比 | 說明 |")
    lines.append("|---|---|---|---|")
    for ft in ["contact_no_pot", "wrong_ball_first", "no_contact", "potted_wrong_pocket", "foul_cue_potted", "other"]:
        count = fail_type_counts.get(ft, 0)
        lines.append(f"| {ft} | {count} | {_pct(count, n_fail):.1f}% | {labels[ft]} |")
    lines.append("")
    lines.append("## 落點誤差（landing_error）統計")
    lines.append("### 全部（成功+失敗）")
    lines.append(stats_block(landing_errors_all))
    lines.append("")
    lines.append("### 成功局")
    lines.append(stats_block(landing_errors_success))
    lines.append("")
    lines.append("### 失敗局")
    lines.append(stats_block(landing_errors_fail))
    lines.append("")
    lines.append("## 自動判讀（程式依規則產生）")
    if findings:
        for f_ in findings:
            lines.append(f"- {f_}")
    else:
        lines.append("- （沒有規則被觸發）")
    lines.append("")

    return "\n".join(lines)


def write_outputs(records: List[dict], out_dir: Path, timestamp: str) -> Tuple[Path, Path, Path]:
    out_dir.mkdir(parents=True, exist_ok=True)
    jsonl_path = out_dir / f"results_{timestamp}.jsonl"
    md_path = out_dir / f"summary_{timestamp}.md"
    csv_path = out_dir / f"summary_{timestamp}.csv"

    write_jsonl(records, jsonl_path)
    write_csv(records, csv_path)
    md_path.write_text(render_summary_md(records, timestamp), encoding="utf-8")

    return jsonl_path, md_path, csv_path