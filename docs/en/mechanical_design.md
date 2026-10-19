# Mechanical Design

## 1. Module taxonomy

OnesArm is built from four module families:

1. **Base** — a sheet-metal or printed base with a mortise-and-tenon interface and four suction cups in the prototype.
2. **Joint modules** — 45° and 90° variants. Each holds a drive, a bearing arrangement and a PCB pocket.
3. **Link modules** — X-X long link, X-Y long link and a short integrated link. The long links use 5 mm 5052 aluminium sheet and 50 × 46 mm carbon-fibre tubes; the short link is a compact sheet-metal part.
4. **End effectors** — parallel gripper (≤ 50 mm object diameter), ultrasonic module (HC-SR04), gas-sensor module (MQ series) and a pen module (16 mm fixture).

![X-X long link](../../media/photos/reference/key_figures/fig5-1_xx_link_render.jpg)

![X-Y long link](../../media/photos/reference/key_figures/fig5-2_xy_link_render.jpg)

## 2. The T/N interface

The interface is derived from two timber joints: the dovetail tenon (wide head, narrow root) and the half-lap cross joint. The top connector is a “T” node; the bottom is an “N” node. The N node slides along the T node in X or Y, so two modules can meet at 90° in either direction. Four M3 holes on each face hold the drive; an M5 screw clamps the module pair. A PCB pocket (30 mm × 58.72 mm on the bottom; an L-shaped pocket on the top) keeps the electronics inside the structure.

The interface is **semi-rigid** by design: it can carry a bending moment and still allow a small deformation, which is useful for impact tolerance but complicates the rigid-body assumption used in the kinematics.

## 3. Links and materials

| Part | Material | Process | Notes |
|---|---|---|---|
| X-X / X-Y long link | 5 mm 5052 aluminium sheet + carbon-fibre tube | Sheet-metal laser cut/bend + tube bonding | M5 nodes; 4 + 4 pieces in the build list |
| Short link | 5 mm 5052 aluminium sheet | Sheet metal | 4 pieces |
| Base plate | 5 mm 5052 aluminium sheet | Sheet metal | 2 pieces |
| Joint housing | 9400A photopolymer resin | SLA 3D print | $E=2.75$ GPa, $\nu=0.44$ |
| Sensor brackets | 9400A resin | SLA 3D print | Gas sensor, ultrasonic, gripper |
| Platform | 4040 European aluminium profile | Cut and bolt | 350 W supply, three test plates |

The 2024 report also describes printed links. The 2025 Chapter 5 revision replaces the long links with the aluminium/carbon-tube construction. Both sets of CAD are retained; do not assume they are interchangeable without checking hole patterns.

## 4. Joint modules and drives

| Revision | Drive | Reduction | Controller | Joint PCB |
|---|---|---|---|---|
| v1 | 15 kgf·cm PWM digital servo (5–9 V, 180°) | Servo internal | Raspberry Pi Pico W (RP2040) | Joint A / Joint B board: 3 PWM, 5 LEDs, 3-way selector |
| v2 | 42BYGH47 stepper | FLE-42-20 planetary, 1:20 | STM32F103C8T6 CAN module; STM32F407ZGT6 bus controller | Controller / Monitor boards with TJA1050 CAN |

The v2 stepper uses a magnetic encoder and a closed-loop controller (model not stated). The v1 servo has a stall torque of about 1.47 N·m and a quoted precision of 0.24°.

![Drive module](../../media/photos/reference/key_figures/fig5-4_drive_module_render.jpg)

**Conflict:** the CAD drive folder is named `FLE-42-20_42BYGH27`, while the report says 42BYGH47. The CAD and the text cannot both be current. Resolve this before ordering, because the motor length and shaft affect the joint housing.

## 5. End effectors

- **Parallel gripper** — lead-screw driven, two jaws, designed for objects up to 50 mm. The CAD includes the lead screw, bearing seat, coupling, inner links and jaws.
- **Ultrasonic module** — HC-SR04 in a printed bracket, digital trigger/echo.
- **Gas-sensor module** — MQ-series analogue sensor in a ventilated printed housing.
- **Pen module** — 16 mm fixture for writing/trajectory tests.

![Prototype](../../media/photos/project/onesarm_prototype_small.jpg)

Each effector mounts on the same T/N interface as a joint module, so the arm can switch tools without a new wrist design.

## 6. Working platform

The v2 platform uses 4040 aluminium profile, a 350 W DC supply, three test positioning plates and an STM32F407ZGT6 CAN controller. The v1 platform used the same profile concept with the Pico W base board and three test plates. The platform is a bench fixture, not a mobile base.

## 7. Manufacturing package

- **3D printing:** 17 part types in the first batch, 8 in the reprint batch. The print notes list quantities for the structural parts. STEP files are in `mechanical/output/3dp/`; STL files are in `mechanical/output/3dp/stl_current/`.
- **Sheet metal:** 10 link connectors, 6 motor supports, 6 flange plates, 4 short-link connectors and 1 base support. STEP files are in `mechanical/output/sheet_metal/`.
- **Carbon tube:** 2 XX, 2 XY, 2 short and 1 base tube, all 50 × 46 mm. STEP files are in `mechanical/output/carbon_tube/`.
- **Platform:** 3 test plates, power support and controller support. STEP files are in `mechanical/output/platform/`.

The original checklists and their images are preserved in `BOM/manufacturing/`. The checklists contain quantities, not tolerances or surface finish; add those before sending parts to a shop.

## 8. CAD inventory

The archive contains 184 SLDPRT and 69 SLDASM files, 49 STEP files and 12 STL files. The categorised copy is under `mechanical/source/` and `mechanical/output/`. The 24 simplified assembly files are nested by permutation:

```text
assemblies/simplified_24/装配/
├── ABC/  AyBxCx, AyBxCy, AyByCx, AyByCy
├── ACB/  AyCxBx, AyCxBy, AyCyBx, AyCyBy
├── BAC/  ByAxCx, ByAxCy, ByAyCx, ByAyCy
├── BCA/  ByCxAx, ByCxAy, ByCyAx, ByCyAy
├── CAB/  CyAxBx, CyAxBy, CyAyBx, CyAyBy
└── CBA/  CyBxAx, CyBxAy, CyByAx, CyByAy
```

## 9. Assembly sequence (high level)

1. Print the joint housings and sensor brackets; clean the T/N sliding faces.
2. Cut and bend the aluminium links; bond the carbon tubes; check the M5 hole alignment.
3. Press the bearings and install the drive in a joint housing.
4. Slide the N node into the T node, insert the M5 screw and set the required relative orientation.
5. Repeat for the chain; fit the base and the selected end effector.
6. Route the FPC/XH harness through the link windows; do not pinch the wires at the joint.
7. Mount the PCBs in their pockets and connect the module harness.
8. Fit the platform, supply and emergency stop before powering the drives.

A detailed checklist is in [assembly_and_replication.md](assembly_and_replication.md).

## 10. Known mechanical risks

- The semi-rigid T/N joint is not a precision bearing; repeatability after reassembly is not measured.
- The printed resin joint is the weakest link in the 10 N load case; the report gives no safety factor.
- The 42BYGH27/47 naming conflict can produce a joint that does not close.
- Carbon-tube bonding and sheet-metal bend tolerances are not specified.
- The 350 W supply and XT60 connectors are v2-only; check the v1 board input before reusing them.
