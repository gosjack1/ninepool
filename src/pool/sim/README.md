# PoolTool 九號球模擬環境

用 [PoolTool](https://github.com/ekiefl/pooltool) 做撞球物理模擬，驗證/優化 `nine_ball_strat.py` 裡的幾何解算策略。

不是 ROS2 package，**不會**被 colcon build，獨立 venv 執行。

## 環境安裝

```bash
cd ~/nineball_ws/src/pool/sim
python3 -m venv .venv
source .venv/bin/activate
pip install "numpy<2.0" pooltool-billiards --extra-index-url https://archive.panda3d.org/
pip install matplotlib optuna
```

**每次開新終端機都要先 `source .venv/bin/activate`**，忘記的話會報 `ModuleNotFoundError: No module named 'pooltool'`。

驗證安裝成功：
```bash
python3 -c "import pooltool as pt; print(pt.__version__)"
```

## 桌子規格（新桌，已實測）

| 參數 | 數值 | 來源 |
|---|---|---|
| l（打球區域長）| 1.120 m | 實測 ±1mm |
| w（打球區域寬）| 0.550 m | 實測 ±1mm |
| 球半徑 R | 0.019 m（38mm直徑）| 商品標示 |
| corner_pocket_width（角袋）| 0.065 m | 實測 |
| side_pocket_width（中袋）| 0.080 m | 實測 |
| 其餘袋口細節（cushion_width等）| 估計值 | 用角袋/中袋寬度對比 default 桌算出縮放比例(0.567)推算，未實測 |

座標慣例：**x軸沿桌寬w(短邊)，y軸沿桌長l(長邊)**，原點在桌角。這個順序容易搞錯，之前有份腳本把座標打反過，母球完全打不到目標球。

## 檔案說明

```
sim/
├── .venv/                      # 獨立虛擬環境，不要commit進git
├── test_my_table.py            # 最小驗證腳本：建桌子、擺2顆球、打一桿，確認事件鏈正確
├── arm_table_frame.py          # 座標轉換層：手臂座標(mm) <-> PoolTool座標(m)
├── nine_ball_env.py            # Gym-style reset()/step()環境，用PoolTool內建規則引擎判定合法/犯規/進球
├── calibrate_weights.py        # 用Optuna對nine_ball_strat.py的評分權重做搜索優化
└── strategy_weights.yaml       # 校準腳本自己的輸出紀錄(實驗記錄，不是正式使用檔案)
```

正式使用的權重檔案在 `../../hiwin_control/hiwin_control/strategy_weights.yaml`，`nine_ball_strat.py` 從那裡讀取。

## 怎麼跑

**1. 驗證環境本身沒問題：**
```bash
python3 test_my_table.py
```
應該看到 `STICK_BALL → BALL_BALL → ... → ROLLING_STATIONARY` 這類事件鏈，沒有跳出 traceback。

**2. 驗證環境介面(reset/step)：**
```bash
python3 nine_ball_env.py
```
會印出初始球位置、打一桿後的reward/legal/turn_over等資訊。

**3. 跑權重校準（會花幾分鐘，看`--n-trials`跟`--n-layouts`大小）：**
```bash
python3 calibrate_weights.py --n-trials 30 --n-layouts 200
```

⚠️ **`--n-layouts` 不要設太小（低於100）**，樣本太小時Optuna找到的"最佳權重"每次跑都會給出完全不同的數字（同一份程式碼跑過4次分別得到661/49/20/40這種天差地遠的結果），不能拿來用。用200以上的樣本，結果才穩定可信。

跑完會印出baseline vs最佳權重的成功率比較，並存一份yaml到`sim/`資料夾（只是實驗紀錄），**要手動確認合理後再複製/合併**到`hiwin_control/hiwin_control/strategy_weights.yaml`才會真正生效。

## 已知的API踩坑（0.6.0版）

跟官方文件對不上的地方，遇到類似錯誤時直接翻`.venv/lib/python3.10/site-packages/pooltool/`裡的原始碼確認，比查文件準：

- `PocketTableSpecs` 不在頂層 `pt.PocketTableSpecs`，要用 `from pooltool.objects import PocketTableSpecs`
- 0.6.0版 `PocketTableSpecs` **沒有** `cushion_nose_radius` 參數（舊版文件有寫，這版拿掉了）
- 合法性/犯規/進球判定用內建的 `pt.get_ruleset(pt.GameType.NINEBALL)` + `pt.get_rack(...)`，不用自己刻規則邏輯

## 目前狀態 / 已知限制

- 只驗證了直球(n=0)跟kiss-ball(n=1)兩種路線，反彈球(reflected_route)還沒接進校準場景
- V0（桿速）固定在2.5m/s，還沒納入優化，這是目前成功率天花板被卡住的主因之一
- `arm_table_frame.py` 的座標轉換用placeholder，新桌的`arm.yaml`(pot0~pot3)還沒重新校準，暫時不能接回真實手臂座標
- 最新校準結果（n=200樣本）：baseline成功率29.5% → 優化後31.9%

## 下一步

1. `simple_route()` 加袋口有效寬度評分（進袋方向 vs 袋口開口法線夾角）
2. 把V0一起納入Optuna搜索範圍
3. 選路邏輯從「分數最高」改成「加入執行誤差擾動後，模擬成功率最高」
4. Throw effect補償（真實物理中切角越大，目標球實際走向偏離幾何預測的量）