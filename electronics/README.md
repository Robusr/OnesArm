# Electronics

## Two revisions

| Revision | Controller | Drive | Boards | Status |
|---|---|---|---|---|
| v1 (2024) | Raspberry Pi Pico W (RP2040) | 15 kgf·cm PWM servo | Base, Joint A, Joint B, Holder/Sensor, Expand Controller | Gerber + BOM present |
| v2 (2024-07 onward) | STM32F103C8T6 CAN modules + STM32F407ZGT6 controller | 42BYGH47 + FLE-42-20 (1:20) | OnesArm Controller, OnesArm Monitor | Gerber + BOM present |

The report chapters 1–4 describe v1; Chapter 5 describes v2. Do not mix boards from the two revisions without checking connectors and supply voltages.

## Layout

```text
electronics/
├── output/
│   ├── gerber/
│   │   ├── controller_monitor/   2 Gerber archives (2024-07)
│   │   └── v1_module_boards/     5 Gerber archives (2024-02/03)
│   ├── bom/
│   │   ├── controller_monitor/   UTF-16 TSV/CSV exports
│   │   └── v1_module_boards/
│   └── silkscreen/               board artwork and icons
└── source/                       (no EDA source available)
```

## Interfaces

- Inter-module: 16P 2.54 mm gold-finger plug/socket (v1).
- Intra-module: 12P 1 mm FPC and XH 3P 2.54 mm (v1).
- v1 joint boards: 3 PWM outputs, 5 LEDs, 3-way servo signal selector.
- v1 holder/sensor board: 2 ADC inputs, 3 PWM outputs.
- v2 controller/monitor BOM: TJA1050 CAN transceiver, LM2596-5.0 regulator, XT60 power connectors, 2 × 20 and 2 × 29 headers.

## Missing sources

Only Gerber, BOM and SolidWorks PCB envelope models are present. There is no EasyEDA/Altium/KiCad project or schematic PDF, so the boards cannot be edited or regenerated. See `../docs/errata.md` E-14.

## Fabrication caution

The Gerber archives are dated 2024-02-17/2024-03-17 (v1) and 2024-07-20 (v2). Check the drill files and board outline before ordering. The 350 W supply and XT60 connectors are rated for the v2 platform; do not apply them to the v1 servo boards without verifying the input range.
