# 机械设计

## 1. 模块分类

OnesArm 由四类模块组成：

1. **底座** — 钣金或打印底座，带榫卯接口；样机底部安装四个乳胶吸盘。
2. **关节模块** — 45° 与 90° 两种，内部容纳驱动、轴承与 PCB。
3. **连杆模块** — X-X 长连杆、X-Y 长连杆与集成短连杆。长连杆采用 5 mm 厚 5052 铝板与 50 × 46 mm 碳纤维管；短连杆为紧凑钣金件。
4. **末端执行器** — 平行夹爪（物体直径 ≤ 50 mm）、超声波模块（HC-SR04）、气体传感器模块（MQ 系列）与手写笔模块（16 mm 夹具）。

![X-X 长连杆](../../media/photos/reference/key_figures/fig5-1_xx_link_render.jpg)

![X-Y 长连杆](../../media/photos/reference/key_figures/fig5-2_xy_link_render.jpg)

## 2. T/N 接口

接口借鉴两种木构节点：燕尾榫（头宽根窄、抗拉拔）与十字刻半榫（方形构件搭接）。连接组件顶部为“T”节点，底部为“N”节点。N 节点可沿 T 节点的 X 或 Y 方向滑入，使两模块以互相垂直的两个方向连接。每个连接面有 4 个 M3 孔固定驱动；M5 螺丝夹紧模块对。底部有 30 mm × 58.72 mm 的 PCB 槽，顶部为 L 形 PCB 槽。

该接口按设计是**半刚性**的：可承受一定弯矩，也允许小变形。这有利于抗冲击，但会破坏运动学中“刚体”假设，需要在精度分析时单独考虑。

## 3. 连杆与材料

| 零件 | 材料 | 工艺 | 备注 |
|---|---|---|---|
| X-X / X-Y 长连杆 | 5 mm 5052 铝板 + 碳纤维管 | 钣金激光切割/折弯 + 管粘接 | M5 节点；制造清单各 4 件 |
| 短连杆 | 5 mm 5052 铝板 | 钣金 | 4 件 |
| 底座板 | 5 mm 5052 铝板 | 钣金 | 2 件 |
| 关节外壳 | 9400A 光敏树脂 | SLA 3D 打印 | $E=2.75$ GPa，$\nu=0.44$ |
| 传感器支架 | 9400A 树脂 | SLA 3D 打印 | 气体、超声波、夹爪 |
| 工作平台 | 4040 欧标铝型材 | 切割、螺栓连接 | 350 W 电源、3 块测试板 |

2024 版报告也描述过打印连杆；2025 年第 5 章改为铝板 + 碳管。两套 CAD 都保留，孔位不同，不能默认可互换。

## 4. 关节模块与驱动

| 版本 | 驱动 | 减速 | 控制器 | 关节板 |
|---|---|---|---|---|
| v1 | 15 kgf·cm PWM 数字舵机（5–9 V，180°） | 舵机内置 | Raspberry Pi Pico W（RP2040） | Joint A/B：3 路 PWM、5 路 LED、3 路信号选择 |
| v2 | 42BYGH47 步进电机 | FLE-42-20 行星减速器，1:20 | STM32F103C8T6 CAN 模块；STM32F407ZGT6 总线控制器 | Controller / Monitor 板，TJA1050 CAN |

v2 步进方案配磁编码器闭环控制器（具体型号未给出）。v1 舵机堵转扭矩约 1.47 N·m，标称精度 0.24°。

![驱动模块](../../media/photos/reference/key_figures/fig5-4_drive_module_render.jpg)

**冲突：** CAD 驱动文件夹名为 `FLE-42-20_42BYGH27`，报告正文却写 42BYGH47。二者不能同时为当前版本。下单前必须确认，因为电机长度与轴径会影响关节外壳。

## 5. 末端执行器

- **平行夹爪** — 丝杆驱动、双夹臂，设计用于 ≤ 50 mm 物体。CAD 含丝杆、轴承座、联轴器、内连杆与夹臂。
- **超声波模块** — HC-SR04 安装在打印支架中，数字触发/回波。
- **气体传感器模块** — MQ 系列模拟传感器，带通风打印外壳。
- **手写笔模块** — 16 mm 夹具，用于书写与轨迹测试。

![样机](../../media/photos/project/onesarm_prototype_small.jpg)

每种末端执行器都使用与关节模块相同的 T/N 接口，因此换工具不需要重新设计腕部。

## 6. 工作平台

v2 平台用 4040 铝型材、350 W 直流电源、3 块测试定位板和 STM32F407ZGT6 CAN 控制器。v1 平台沿用相似型材结构，配 Pico W 主板与 3 块测试板。该平台是台式工装，不是移动底盘。

## 7. 制造包

- **3D 打印：** 首批 17 种零件，补印 8 种。打印备注列出结构件数量。STEP 文件在 `mechanical/output/3dp/`，STL 在 `mechanical/output/3dp/stl_current/`。
- **钣金：** 10 个连杆连接组件、6 个电机支撑、6 个法兰连接板、4 个短连杆连接组件、1 个底座支撑。STEP 在 `mechanical/output/sheet_metal/`。
- **碳管：** XX 长 2 根、XY 长 2 根、短 2 根、底座 1 根，均为 50 × 46 mm。STEP 在 `mechanical/output/carbon_tube/`。
- **平台：** 3 块测试定位板、电源支撑、控制器支撑。STEP 在 `mechanical/output/platform/`。

原始清单与图片保存在 `BOM/manufacturing/`。清单只有数量，没有公差与表面处理；送厂前需补充。

## 8. CAD 资产

归档含 184 个 SLDPRT、69 个 SLDASM、49 个 STEP、12 个 STL。分类副本在 `mechanical/source/` 与 `mechanical/output/`。24 个简化装配体按排列分组：

```text
assemblies/simplified_24/装配/
├── ABC/  AyBxCx, AyBxCy, AyByCx, AyByCy
├── ACB/  AyCxBx, AyCxBy, AyCyBx, AyCyBy
├── BAC/  ByAxCx, ByAxCy, ByAyCx, ByAyCy
├── BCA/  ByCxAx, ByCxAy, ByCyAx, ByCyAy
├── CAB/  CyAxBx, CyAxBy, CyAyBx, CyAyBy
└── CBA/  CyBxAx, CyBxAy, CyByAx, CyByAy
```

## 9. 装配顺序（概要）

1. 打印关节外壳与传感器支架；清理 T/N 滑动面。
2. 切割、折弯铝连杆；粘接碳管；检查 M5 孔位。
3. 压入轴承，把驱动装入关节外壳。
4. 将 N 节点滑入 T 节点，插入 M5 螺丝，设定所需相对方向。
5. 逐节重复，装上底座与选定末端执行器。
6. 让 FPC/XH 线束穿过连杆窗口，避免在关节处被夹住。
7. 将 PCB 装入槽内，连接模块线束。
8. 装上平台、电源与急停后再给驱动上电。

详细步骤见[装配与复现](assembly_and_replication.md)。

## 10. 已知机械风险

- 半刚性 T/N 节点不是精密轴承；重复拆装后的重复定位精度未测。
- 10 N 载荷下，打印树脂关节是最薄弱环节；报告未给安全系数。
- 42BYGH27/47 命名冲突可能导致关节装不闭合。
- 碳管粘接与钣金折弯公差未规定。
- 350 W 电源与 XT60 仅属于 v2；复用前必须核对 v1 板卡输入范围。
