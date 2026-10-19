# 电子与控制

## 1. 两个版本

OnesArm 有两套有文档的电子平台，二者引脚不兼容。

| 项目 | v1（2024，报告第 2–4 章） | v2（2024-07 起，报告第 5 章） |
|---|---|---|
| 控制器 | Raspberry Pi Pico W（RP2040，133 MHz，Wi-Fi） | STM32F103C8T6 CAN 模块 + STM32F407ZGT6 控制器 |
| 驱动 | 15 kgf·cm PWM 舵机 | 42BYGH47 步进 + FLE-42-20（1:20） |
| 反馈 | 舵机内部 | 磁编码器闭环控制器 |
| 模块总线 | 16P 2.54 mm 金手指 | CAN（TJA1050 收发器） |
| 模块供电 | 5–9 V 舵机电源 | 350 W 直流电源，XT60 |
| 板卡 | Base、Joint A、Joint B、Holder/Sensor、Expand Controller | OnesArm Controller、OnesArm Monitor |

## 2. v1 架构

Pico W 主板引出 SPI、I2C 扩展口与独立供电入口。Joint A/B 板各有 3 路 PWM、5 路状态 LED 与 3 路舵机信号选择（跳线帽）。Holder/Sensor 板提供 2 路 ADC 与 3 路 PWM。Expand Controller 增加 GNSS、0.96 英寸单色 OLED、8 × 2P 金手指调试排针与 USB Type-B 外部供电。

![关节模块 PCB](../../media/photos/reference/key_figures/fig2-19_pcb_joint_module.png)

![主板 PCB](../../media/photos/reference/key_figures/fig2-19_pcb_base_module.png)

模块内部用 12P 1 mm FPC 与 XH 3P 2.54 mm 端子线；模块之间用 16P 2.54 mm 金手指插头/插座。连接紧凑但没有防反插结构，每根线都必须标记 1 脚。

## 3. v2 架构

Controller 与 Monitor 板使用 TJA1050 CAN 收发器、LM2596-5.0 降压、XT60 电源接口、2 × 20 与 2 × 29 排针、4 个按键与状态 LED。BOM 未列 MCU 芯片，因为 STM32 模块插在排针上。350 W 电源同时供给步进驱动与总线控制器。

归档没有记录 CAN 波特率、节点 ID、终端电阻与报文布局。连接多个关节模块前必须先定义这些参数。

## 4. 供电

- v1：舵机 5–9 V；Pico W 需稳定 5 V。Expand Controller 可接 USB Type-B 外部供电。
- v2：350 W 直流电源经 XT60 输入；LM2596 提供 5 V 逻辑电源。上电前核对每个步进驱动的输入范围。
- 应增加保险丝、反接保护与急停。归档板卡上未看到这些电路。

## 5. 固件现状

| 工程 | 状态 |
|---|---|
| `firmware/stm32/demo_LED` | CubeMX 骨架，用户循环为空 |
| `firmware/stm32/demo_LED1` | CubeMX 骨架 |
| `firmware/stm32/demo_test` | GPIO + RTC 骨架 |
| `firmware/stm32/Key` | 按键驱动有编译错误，头文件为空 |
| `firmware/stm32/KeyLED` | 用户代码为空 |
| `firmware/stm32/彩色液晶屏驱动...` | LCD 驱动工程，使用前核对接线 |

所有 HAL 配置中的 CAN 都被注释掉。没有舵机 PWM、步进脉冲或 CAN 应用代码。这些工程可作为时钟/引脚参考，不能直接当机械臂控制器。

MicroPython 只有 SSD1306 OLED 驱动与 L76X/micropyGPS GNSS 库，没有 `main.py`，也没有机械臂运动学。报告所述 MicroPython 开环测试无法由归档代码复现。见[勘误 E-11](../errata.md)。

## 6. 上电顺序

1. 检查板卡焊桥与极性；先不要插 MCU 模块。
2. 用限流电源加 5 V，检查 3.3 V 轨与电流。
3. 插上 MCU 模块，烧录对应 CubeMX 工程的 LED 闪烁程序。
4. 在台架上测试单路舵机或步进，不装机械臂。
5. 接一个关节模块，确认 CAN 或 PWM 信号，再增加下一节。
6. 最后才装配整臂，并从小幅低速轨迹开始。

## 7. 缺失的设计源文件

归档只有 Gerber、BOM 与 SolidWorks PCB 外形模型，没有 EasyEDA/Altium/KiCad 工程或原理图 PDF，因此板卡不能修改或重新生成。发布“可制造版本”前应找回 EDA 源文件。见[勘误 E-14](../errata.md)。

## 8. 物料清单

摘要见 [`../../BOM/onesarm_bom.md`](../../BOM/onesarm_bom.md)，原始 PCB BOM 见 [`../../electronics/output/bom/`](../../electronics/output/bom/)。
