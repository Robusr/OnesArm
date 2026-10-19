# OnesArm — 技术文档（中文）

OnesArm（珠联“臂”合）是一台可重构的模块化串联机械臂。本目录是仓库 README 的长文档版本。

## 目录

- [工作原理](theory_of_operation.md) — 模块化结构、FCF 抽象、24 种组合、DH 运动学、工作空间、优化指标与静力学。
- [机械设计](mechanical_design.md) — 连杆、关节、T/N 榫卯接口、材料、末端执行器、工作平台与制造。
- [电子与控制](electronics_and_control.md) — v1 Pico W 舵机平台、v2 STM32 CAN 步进平台、板卡、接口与固件现状。
- [装配与复现](assembly_and_replication.md) — 版本选择、零件制造、装配、接线、分析与测试步骤。

## 审查文档

- [勘误](../errata.md)
- [验证](../verification.md)
- [术语表](../glossary.md)
- [参考文献](../references/README.md)

设计表使用毫米，复算输出使用米；设计表使用角度，公式使用弧度。涉及单位的地方均会明确标注。
