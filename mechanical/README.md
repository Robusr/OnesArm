# Mechanical

```text
mechanical/
├── source/          SolidWorks parts and assemblies
│   ├── links/       X-X / X-Y / short links (legacy 2024 and current)
│   ├── joints/      45° and 90° joint modules
│   ├── base/        base plates and supports
│   ├── end_effectors/ gripper, pen, ultrasonic, gas sensor
│   ├── drive/       motor/gearbox models (FLE-42-20 + 42BYGH27)
│   ├── platform/    working platform and fixture plates
│   ├── standard_parts/ screws, nuts, profiles, flanges
│   ├── assemblies/  current, legacy and 24 simplified combinations
│   ├── fea_models/  SolidWorks static-study models
│   └── pcb_3d_models/
├── output/
│   ├── 3dp/         STEP and STL print files
│   ├── sheet_metal/ STEP
│   ├── carbon_tube/ STEP
│   └── platform/    STEP
└── analysis/fea/    exported stress/displacement images (no .CWR caches)
```

## What is verified

- 24 three-module combinations exist as SLDASM files (`assemblies/simplified_24/装配/ABC|ACB|BAC|BCA|CAB|CBA`), plus 3 single-joint models. The count matches \(3!\,2^{3-1}=24\).
- 49 STEP files and 12 STL files are present across the print batches and current design.
- The 2025 revision specifies 5 mm 5052 aluminium sheet and 50 × 46 mm carbon tubes, joined at standardized nodes with M5 screws.

## Material assignment

- **Links:** 5 mm 5052 aluminium sheet + carbon-fibre tube (v2; the 2024 text also describes printed links).
- **Joint housings and sensor brackets:** 9400A photopolymer resin (SLA), \(E=2.75\) GPa, \(\nu=0.44\), density 1150 kg/m³.
- **Standard parts:** M3/M5 screws, nuts, flanges and 4040 aluminium profile.

## Manufacturing notes

- 3D print: two checklists (17 part types, then 8 reprints). See `../BOM/manufacturing/`.
- Sheet metal: 10 link connectors, 6 motor supports, 6 flange plates, 4 short-link connectors, 1 base support.
- Carbon tube: 2 XX, 2 XY, 2 short, 1 base, all 50 × 46 mm.
- SolidWorks solver caches (`.CWR`, `.BD2`, `.BDF`, `.MFC`, `.SL4`) were **not** copied; they are regenerable and several exceed 100 MB.

## Known conflict

The drive folder is named `FLE-42-20_42BYGH27`, while report Chapter 5 says 42BYGH47. The v1 servo models and the v2 stepper models are both present. Freeze the revision before ordering or machining. See `../docs/errata.md` E-10.
