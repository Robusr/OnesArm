# OnesArm Bill of Materials

This is a **build-planning summary**, not a validated procurement list. The project has two documented hardware revisions. Read the revision column before ordering parts.

| Subsystem | Item | Specification | Qty | Revision | Source |
|---|---|---|---:|---|---|
| Structure | X-X long link | 5 mm 5052 aluminium sheet + 50 x 46 mm carbon tube | 4 | v1/v2 | Report 2.2 / 5.2.1; `manufacturing/定做生产.md` |
| Structure | X-Y long link | 5 mm 5052 aluminium sheet + 50 x 46 mm carbon tube | 4 | v1/v2 | Report 2.2 / 5.2.1; `manufacturing/定做生产.md` |
| Structure | Short link | 5 mm 5052 aluminium sheet | 4 | v1/v2 | `manufacturing/定做生产.md` |
| Structure | Base plate | 5 mm 5052 aluminium sheet | 2 | v1/v2 | `manufacturing/定做生产.md` |
| Structure | Motor support | Sheet metal | 6 | v1/v2 | `manufacturing/定做生产.md` |
| Structure | Flange connecting plate | Sheet metal | 6 | v1/v2 | `manufacturing/定做生产.md` |
| Carbon tube | XX / XY / short / base tubes | 50 x 46 mm | 2 / 2 / 2 / 1 | v1/v2 | `manufacturing/定做生产.md` |
| Joint | 45 degree joint module | Drive + bracket | 1 | v1/v2 | Report 2.3.4 / 5.2.2 |
| Joint | 90 degree joint module | Drive + bracket | 2 | v1/v2 | Report 2.3.4 / 5.2.2 |
| Drive v1 | Digital servo | 15 kgf.cm; 5-9 V; PWM; 180 deg | 3 | v1 | Report 2.3.1 |
| Drive v2 | Stepper + reducer | 42BYGH47 + FLE-42-20 (1:20) | 3 sets | v2 | Report 5.2.2 |
| Control v1 | Raspberry Pi Pico W | RP2040; Wi-Fi | 1 | v1 | Report 2.3.2 |
| Control v2 | CAN modules | STM32F103C8T6 + STM32F407ZGT6 | 3 + 1 | v2 | Report 5.2.2 / 5.2.3 |
| Power | DC supply | 350 W | 1 | v2 | Report 5.2.3 |
| Platform | Frame | 4040 aluminium profile | 1 | v2 | Report 5.2.3 |
| End effector | Gripper | <= 50 mm object diameter | 1 | v1/v2 | Report 2.3.3 |
| End effector | Ultrasonic | HC-SR04 | 1 | v1/v2 | Report 2.3.3 |
| End effector | Gas sensor | MQ series | 1 | v1/v2 | Report 2.3.3 |

## Revision conflict

The report chapters 1-4 describe a **15 kgf.cm servo + Raspberry Pi Pico W** prototype. Chapter 5 (added in the 2025 revision) describes a **42BYGH47 stepper + FLE-42-20 reducer + STM32 CAN** platform. The CAD drive folder is named `FLE-42-20_42BYGH27`, while the text says 42BYGH47. Pick one revision before ordering. See `docs/errata.md` E-10.

## Detailed sources

- 3D-print checklists: [`manufacturing/3D打印/3D打印清单.md`](manufacturing/3D打印/3D打印清单.md) and [`manufacturing/3D打印补印/3D打印清单.md`](manufacturing/3D打印补印/3D打印清单.md)
- Sheet-metal checklist: [`manufacturing/钣金攻丝/清单.md`](manufacturing/钣金攻丝/清单.md)
- Carbon-tube checklist: [`manufacturing/碳管定做/清单.md`](manufacturing/碳管定做/清单.md)
- Platform checklist: [`manufacturing/工作平台定位板/清单2.md`](manufacturing/工作平台定位板/清单2.md)
- PCB BOMs: [`../electronics/output/bom/controller_monitor/`](../electronics/output/bom/controller_monitor/) and [`../electronics/output/bom/v1_module_boards/`](../electronics/output/bom/v1_module_boards/)
- Gerber archives: [`../electronics/output/gerber/`](../electronics/output/gerber/)

## Licence note

The BOM is a derived summary of the author's report and manufacturing notes. It is documentation, covered by `LICENSE-docs.md`. Third-party component names and trademarks remain with their owners.
