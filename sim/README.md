# sim/ —— MuJoCo 自碰撞模擬模型

這個資料夾存放 HIWIN RA605-710-GB 手臂 + 新末端(斜桿+主副電磁閥)的 MuJoCo 碰撞模型,
以及自碰撞可行域掃描腳本。跟 `src/` 底下的 ROS2 套件是分開的獨立工具,不需要 colcon build。

## 資料夾結構

```
sim/
  ra605_full.xml          MuJoCo 主模型檔(手臂本體 + 末端 + 碰撞排除清單)
  self_collision_scan.py  自碰撞可行域掃描腳本
  feasibility_map.csv     掃描腳本目前的輸出範例(測試流程用,非完整覆蓋)
  meshes/
    RT605-001.stl ~ RT605-007.stl   手臂本體 7 個連桿的碰撞網格
    end_effector_main.stl           末端斜桿主體
  README.md                本檔案
```

## 這份模型是怎麼來的(生成流程)

### 1. 手臂本體連桿網格 —— 從官方 STEP 檔匯出

來源檔案:`RT605-710-GB_3D_v3.stp`(HIWIN 官方,Autodesk Inventor 2020 匯出,
從 `hiwinsupport.com` 的 2D/3D CAD 下載中心取得,Multi-Axis Robot 分類)。

用 OCP(OpenCASCADE 的 Python binding)解析 STEP 檔案的組裝結構,確認裡面乾淨拆成
7 個獨立零件(`RT605-001` ~ `RT605-007`,對應底座+6 軸)+ 1 個連接器線材零件
(`605-CN2`,幾何是參數化曲線、不是實體,已排除)。

每個零件用**局部設計座標系**(不是組裝後的世界座標)匯出成 STL,網格精度用
1mm 線性誤差、0.3 rad 角度誤差做粗化(適合碰撞檢測用,不需要精細加工級網格)。

```python
# 關鍵 API:
from OCP.STEPCAFControl import STEPCAFControl_Reader
from OCP.XCAFDoc import XCAFDoc_DocumentTool, XCAFDoc_ShapeTool
# shape_tool.GetShape_s(ref_lbl) 拿到零件「局部座標系」的 shape(不套用組裝變換)
# BRepMesh_IncrementalMesh(shape, 1.0, False, 0.3, True) 做網格化
# StlAPI_Writer 輸出 STL(ASCIIMode=False 用二進位格式,檔案小很多)
```

### 2. 運動學鏈 —— 用官方 DH 表建構、數值驗證

DH 參數(RT605-710-GB,710mm 版本):

| Joint | α(i-1) | a(i-1) | d(i) | θ(i) | 限位(deg) |
|---|---|---|---|---|---|
| 1 | 0 | 0 | 338 | θ1 | ±165 |
| 2 | -90 | 67 | 0 | θ2-90 | +85/-125 |
| 3 | 0 | 375 | 0 | θ3 | +185/-55 |
| 4 | -90 | 0 | 375 | θ4 | ±190 |
| 5 | 90 | 0 | 0 | θ5 | ±115 |
| 6 | -90 | 0 | 60 | θ6 | ±360 |

標準 DH 轉換 `T_i = Rx(α_{i-1}) · Tx(a_{i-1}) · Tz(d_i) · Rz(θ_i)`,拆解成:
- **body 的 pos/quat**(固定部分,不含 θ_i):`Rx(α_{i-1}) · Tx(a_{i-1}) · Tz(d_i)`
- **joint 的旋轉**(θ_i):hinge, axis="0 0 1",物理角度由呼叫端在執行期提供

**⚠️ 極重要,務必記住**:
- MJCF 裡的關節**故意不使用 `ref` 屬性**。測試證實 `ref` 會跟手動設定的 qpos
  疊加(而非取代),混用會造成角度算錯 90°/180° 這類難以察覺的錯誤。
- **J2 的角度換算**必須由呼叫端手動處理:
  ```python
  qpos_J2_sim = controller_J2_degrees - 90   # 對應 DH 表 θ2 = θ2' - 90
  # 其餘五軸(J1,J3,J4,J5,J6)直接 1:1 對應,不用轉換
  ```

驗證方式:六軸 qpos 全部設為 DH 零位角度(J2 物理角度 = -90°),flange 世界座標
應落在 `(502, 0, 713)` mm,與 DH 手算正向運動學完全吻合(誤差 < 0.001mm)。

### 3. 網格對齊到關節鏈

每個連桿的 STL(局部座標系版本)直接掛在對應 body 底下、**不加額外 offset**
(`pos="0 0 0"`),前提假設是「零件局部設計原點 = 該連桿對應的 DH 關節軸」。

驗證方式(兩種,互相佐證):
1. Link1 用局部 bounding box 對稱性分析驗證(X 方向 [-97.4,97.4] 完美對稱,
   代表原點落在旋轉對稱軸上)。
2. 全部 7 個連桿 render 成單獨的圖(每張標示局部原點+XYZ軸),目視確認原點
   位置都落在正確的關節面上。

### 4. 排除清單(避免相鄰連桿誤判碰撞)

```xml
<contact>
  <exclude body1="base"  body2="link1"/>
  <exclude body1="link1" body2="link2"/>
  <exclude body1="link2" body2="link3"/>
  <exclude body1="link3" body2="link4"/>
  <exclude body1="link4" body2="link5"/>
  <exclude body1="link5" body2="link6"/>
</contact>
```

原則:直接父子關係(相鄰關節)要排除,隔代的(如 link1 vs link4)絕對不排除
——這才是真正要抓的自撞情況(手肘折太緊撞到別的連桿)。

### 5. 末端執行器 —— 近似對齊版本(⚠️ 尚未用精確孔位驗證)

來源:`要硬了.stl`(使用者上傳,Bambu Studio 切片前的原始模型)。
用 trimesh 拆出的兩個連通元件中,只保留主體斜桿(`end_effector_main.stl`);
另一個小零件(15×15×19mm)經確認跟末端無關(列印盤上順便印的其他物件),
已從模型中移除,不建入碰撞幾何。

對齊方式:
1. 取頂部 45mm 範圍內的頂點,PCA 找出連接面的法向量與中心點。
2. 用 Rodrigues 旋轉公式,把這個法向量對齊到 link6 局部座標系的 +Z 方向。
3. 平移,讓連接面中心落在 link6 局部座標系 `(0,0,2)`(2mm 間隙)。
4. 加一片實心連接板(`mount_plate` geom,48×66mm,尺寸取自連接面實測投影範圍),
   從 J6(z=0)延伸到末端安裝面(z=2),兩邊相切、不留縫也不重疊,取代還沒
   量到的四孔精確座標。

**已知限制,之後一定要修正**:這個對齊只解決了「連接面朝向哪個方向」,
**沒有解決末端繞著這個法向量自轉的角度(roll)**——目前這個角度是任意值,
不對應真實機構設計方向。掃描測試已經證實:這個未鎖定的 roll 角度會讓
`ee_main` 跟 `geom_link4` 在幾乎所有姿態下都判定碰撞,這不代表真實自撞,
只是這個角度剛好讓末端體積長期跟 link4 重疊。

**修正方法**:等連接板四個鎖孔的精確座標從 Fusion 360 量出來後,額外解一個
繞法向量的旋轉角,讓斜桿轉到跟孔位對應的真實方向,取代現在這個任意角度。
只需要重新跑一次 mesh transform,不用重寫其他部分。

### 6. 自碰撞掃描腳本

`self_collision_scan.py` 目前是**第一版、尚未接 IK**——直接對六軸角度本身
做網格掃描(而不是對「hitpoint + 瞄準角」做掃描)。等 HIWIN 控制器的 IK
查詢介面接上後,要把「角度來源」從直接掃描改成呼叫 IK 算出來的結果,
其他部分(碰撞檢查、CSV 輸出)不用改。

已驗證:排除末端(只測手臂本體自己)時,測試範圍內 0 碰撞,證實掃描機制
本身正確;加入末端後,幾乎 100% 判定碰撞,已確認是上述 roll 角度未鎖定
造成的已知限制,不是程式邏輯錯誤。

## 操作步驟

### 安裝

```bash
python3 -m venv ~/venvs/mujoco_env
source ~/venvs/mujoco_env/bin/activate
pip install mujoco numpy
```

### 載入模型、跑正向運動學檢查

```bash
python3 -c "
import mujoco, numpy as np
m = mujoco.MjModel.from_xml_path('ra605_full.xml')
d = mujoco.MjData(m)
# 範例:六軸控制器角度 [0,0,0,0,0,0](J2 會自動換算 -90)
thetas = [0,-90,0,0,0,0]  # 這裡直接填物理角度(已含 -90)方便對照 DH
for n,deg in zip(['J1','J2','J3','J4','J5','J6'], thetas):
    d.qpos[m.jnt_qposadr[m.joint(n).id]] = np.radians(deg)
mujoco.mj_forward(m,d)
print(d.site('flange').xpos)  # 應輸出約 [502, 0, 713]
"
```

### 跑自碰撞掃描

```bash
python3 self_collision_scan.py
# 輸出:feasibility_map.csv
```

呼叫端要注意:`SelfCollisionChecker.check()` 吃的是**控制器回報角度**
(J2 未減 90),函式內部會自動處理換算,外部不要重複減。

### 互動式視覺化(需要有顯示器/桌面環境的機器,不是 headless 伺服器)

```bash
python3 -m mujoco.viewer --mjcf=ra605_full.xml
```

可以拖曳滑鼠轉視角、用面板滑桿手動拖動每一軸角度,適合用來手動摸索
「近端自撞邊界」的大致範圍。

### 生成動畫(headless 環境,離屏渲染)

```bash
MUJOCO_GL=egl python3 -c "
import mujoco, numpy as np
from PIL import Image
m = mujoco.MjModel.from_xml_path('ra605_full.xml')
d = mujoco.MjData(m)
renderer = mujoco.Renderer(m, height=600, width=800)
# ...(依需求設計關節角度序列,逐幀 render,存成 GIF)
"
```

需要 `<visual><global offwidth="960" offheight="720"/></visual>` 這類設定
把離屏 framebuffer 開夠大(已經寫進 `ra605_full.xml` 裡)。

## 待辦清單(尚未完成)

- [ ] 末端連接板四孔精確座標(Fusion 360 量測),用來鎖定 roll 角度
- [ ] 副電磁閥的碰撞幾何 + TCP 校正(目前只有主電磁閥 tool 8 校正完成)
- [ ] IK 求解器對接 HIWIN 控制器(掃描腳本目前繞過這塊,直接掃六軸角度)
- [ ] 完整範圍的自碰撞可行域掃描(目前只有小範圍流程測試)
- [ ] 近端自撞邊界(手臂基座附近)的實機或模擬驗證結果,轉成查表格式接進
      `nine_ball_strat.py`
