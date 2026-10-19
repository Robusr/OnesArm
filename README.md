<p align="center">
  <img src="./media/photos/project/banner.jpg" alt="OnesArm v2 modular robotic arm on a 4040 aluminium platform" width="900"/>
</p>

<h1 align="center">OnesArm</h1>

<p align="center">
  <strong>A modular serial robotic arm for multi-scenario tasks</strong>
  <br>
  v2 stepper/CAN platform, 24 joint layouts, and mortise-and-tenon interfaces
</p>

<p align="center">
  <a href="./LICENSE.md"><img src="https://img.shields.io/badge/code-MIT-blue.svg" alt="Code: MIT"></a>
  <a href="./LICENSE-docs.md"><img src="https://img.shields.io/badge/docs%20%26%20CAD-CC%20BY%204.0-lightgrey.svg" alt="Docs and CAD: CC BY 4.0"></a>
  <img src="https://img.shields.io/badge/CAD-SolidWorks-e63946" alt="SolidWorks">
  <img src="https://img.shields.io/badge/control-STM32%20CAN-00549f" alt="STM32 CAN">
  <img src="https://img.shields.io/badge/platform-350%20W-2e7d32" alt="350 W platform">
  <img src="https://img.shields.io/badge/status-v2%20current-brightgreen" alt="v2 current">
</p>

<p align="center">
  <a href="./README.md">English</a> |
  <a href="./README.zh-CN.md">中文</a> |
  <a href="./README.fr.md">Français</a>
</p>

---

## About the project

**OnesArm** (Chinese project title: 珠联“臂”合) is a modular serial robotic arm. **v2 is the current platform.** It combines 42BYGH47 stepper motors with FLE-42-20 planetary reducers, STM32F103C8T6 CAN joint modules, an STM32F407ZGT6 bus controller, a 350 W supply and a 4040 aluminium platform. The links use 5 mm 5052 aluminium sheet and 50 × 46 mm carbon-fibre tubes, joined at standardised M5 nodes.

The arm is assembled from interchangeable joint, link and end-effector modules through **T/N mortise-and-tenon** interfaces. For the three-module configuration, the base-adjacent orientation is fixed and the other two modules choose one of two perpendicular channels, giving

$$
N_3 = 3! \cdot 2^{3-1} = 24
$$

joint layouts. The 24 assemblies are modelled in SolidWorks.

The earlier **v1 reference build**, with 15 kgf·cm PWM servos and a Raspberry Pi Pico W, is retained in the repository for comparison. The project was developed by 郭沫晗 (Guo Mohan) at Guyuan No. 1 Middle School, Ningxia. The report documents a first prize at the 38th National Youth Science and Technology Innovation Competition (2024).

> **Platform note.** v1 and v2 use separate electronics. Select the matching drive and board set before assembly.

## Key features

- **v2 stepper/CAN drive chain** — 42BYGH47 motors, FLE-42-20 1:20 reducers, magnetic encoder closed-loop control and STM32F103C8T6 CAN joint modules.
- **v2 aluminium/carbon structure** — 5 mm 5052 links, 50 × 46 mm carbon tubes, M5 nodes, a 4040 platform and a 350 W supply, with SolidWorks, STEP and STL sources included.
- **24 reconfigurable layouts** — three interchangeable modules, two perpendicular channels, and a fixed base-adjacent orientation.
- **T/N mortise-and-tenon interface** — a T node on top and an N node below, clamped by an M5 screw, inspired by dovetail and half-lap timber joints.
- **v1 reference build** — 15 kgf·cm PWM servos, Raspberry Pi Pico W, five module boards and a 16P gold-finger interconnect.
- **Multi-scenario end effectors** — parallel gripper, HC-SR04 ultrasonic probe, MQ gas sensor and pen module share the same interface.

## System architecture

### v2 current platform

```text
                    ┌──────────────────────────────┐
                    │  End effector                │
                    │  gripper / ultrasonic / gas  │
                    └──────────────┬───────────────┘
                                   │ T/N interface
                    ┌──────────────┴───────────────┐
                    │  Link module (XX / XY / short)│
                    │  5 mm 5052 + carbon tube      │
                    └──────────────┬───────────────┘
                                   │
                    ┌──────────────┴───────────────┐
                    │  Joint module (45° / 90°)     │
                    │  42BYGH47 + FLE-42-20 + CAN   │
                    └──────────────┬───────────────┘
                                   │
                    ┌──────────────┴───────────────┐
                    │  4040 platform + 350 W supply │
                    │  STM32F407ZGT6 CAN controller │
                    └──────────────────────────────┘
```

| Subsystem | v2 implementation |
|---|---|
| Controller | STM32F407ZGT6 CAN bus controller; STM32F103C8T6 CAN module in each joint |
| Drive | 42BYGH47 stepper + FLE-42-20 planetary reducer, 1:20; magnetic encoder closed-loop |
| Bus and power | CAN via TJA1050; 350 W DC supply; XT60 input; LM2596-5.0 logic rail |
| Structure | 5 mm 5052 aluminium sheet + 50 × 46 mm carbon tubes; M5 nodes; 4040 aluminium platform |
| End effectors | Parallel gripper, HC-SR04 ultrasonic probe, MQ gas sensor, pen module |

<p align="center">
  <img src="./media/photos/reference/key_figures/fig5-1_xx_link_render.jpg" alt="v2 X-X long link render" width="340"/>
  <img src="./media/photos/reference/key_figures/fig5-2_xy_link_render.jpg" alt="v2 X-Y long link render" width="340"/>
  <br>
  <em><strong>Figure 1 — v2 long links.</strong> X-X and X-Y links in 5 mm 5052 aluminium with 50 × 46 mm carbon tubes and M5 connection nodes.</em>
</p>

<p align="center">
  <img src="./media/photos/reference/key_figures/fig5-4_drive_module_render.jpg" alt="v2 stepper and reducer module" width="380"/>
  <img src="./media/photos/reference/key_figures/fig5-5_working_platform.jpg" alt="v2 arm on a 4040 platform" width="520"/>
  <br>
  <em><strong>Figure 2 — v2 drive module and platform.</strong> 42BYGH47 stepper, FLE-42-20 reducer, CAN board and the 4040 aluminium working platform.</em>
</p>

### v1 reference build

| Subsystem | v1 implementation |
|---|---|
| Controller | Raspberry Pi Pico W, RP2040, Wi-Fi |
| Drive | 15 kgf·cm PWM digital servo |
| Bus | 16P 2.54 mm gold-finger interconnect |
| Boards | Base, Joint A, Joint B, Holder/Sensor, Expand Controller |
| Supply | 5–9 V servo rail; 5 V logic |

<p align="center">
  <img src="./media/photos/project/banner_v1.jpg" alt="v1 reference build render" width="520"/>
  <img src="./media/photos/reference/key_figures/fig2-19_pcb_joint_module.png" alt="v1 joint module PCB" width="360"/>
  <br>
  <em><strong>Figure 3 — v1 reference build.</strong> Servo-driven arm render and the Joint Module PCB with PWM outputs, status LEDs and a servo signal selector.</em>
</p>

## Theory and design

### Modular combinations

The report abstracts the chain as **Connecting Face – Connecting Channel – Connecting Face** (FCF). An X-X or X-Y long link has 6 faces × 4 channels; a short link has 4 × 4; a joint has 2 × 4. For the three-module configuration, the 45° module and two 90° modules can be ordered in $3!$ ways; the base-adjacent orientation is fixed, and the other two orientations give $2^2$. The result is 24, verified by 24 CAD assemblies plus 3 single-joint models.

<p align="center">
  <img src="./media/photos/reference/key_figures/fig5-7_fcf_structure.png" alt="Connecting face - connecting channel - connecting face" width="520"/>
  <img src="./media/photos/reference/key_figures/fig5-8_concat_structure.png" alt="Concatenated modular chain" width="520"/>
  <br>
  <em><strong>Figure 4 — FCF abstraction.</strong> Every connection is a face, a channel and another face. Long links have six faces, short links four, and joints two.</em>
</p>

### Kinematics

The analysed configuration is **AyCxBy-D**, a 4-DOF chain. Report Table 3-20 gives:

| $i$ | $d_i$ (mm) | $a_i$ (mm) | $\alpha_i$ | Report range |
|---:|---:|---:|---:|---|
| 1 | 95 | 0 | 90° | 0° |
| 2 | 0 | 113.5 | 90° | 0–180° |
| 3 | 21.34 | 88.5 | 90° | 0–180° |
| 4 | 0 | 152 | 0° | 0–180° |

The verification model uses standard DH:

$$
T_i = \operatorname{Rot}_z(\theta_i)\,\operatorname{Trans}_z(d_i)\,
\operatorname{Trans}_x(a_i)\,\operatorname{Rot}_x(\alpha_i).
$$

The link-length sum is $113.5 + 88.5 + 152 = 354$ mm. With the model offsets, the sampled workspace reaches about **450 mm**.

<p align="center">
  <img src="./media/photos/reference/key_figures/fig3-29_workspaces.png" alt="Workspace comparison for four assembly layouts" width="760"/>
  <br>
  <em><strong>Figure 5 — Workspace comparison.</strong> Four of the 24 layouts: AyCxBy-D, AyCyBx-D, AyCxBx-D and AyCyBy-D. Simulation samples from the kinematic model.</em>
</p>

Assembly selection compares workspace envelopes and a kinematic effort index over the 24 layouts. The workspace study covers the four representative layouts shown above.

### Static analysis

The static study uses 9400A photopolymer resin and a 10 N load on each joint top face. The joint housings and the full assembly are evaluated in SolidWorks Simulation.

<p align="center">
  <img src="./media/photos/reference/key_figures/fig3-2_fea_mesh.png" alt="Finite element mesh of the joint housing" width="380"/>
  <img src="./media/photos/reference/key_figures/fig3-5_fea_stress.png" alt="Static stress result for the joint housing" width="380"/>
  <br>
  <em><strong>Figure 6 — Static analysis.</strong> Mesh and stress result for the joint housing under the 10 N load case.</em>
</p>

## Repository structure

```text
OnesArm/
├── BOM/                    summary + manufacturing checklists
├── electronics/            Gerber, BOM and silkscreen outputs
├── mechanical/
│   ├── source/             SolidWorks parts and assemblies
│   ├── output/             STEP, STL and fabrication exports
│   └── analysis/fea/       exported FEA images
├── firmware/               STM32CubeIDE projects + MicroPython libraries
├── software/               MATLAB kinematics scripts
├── docs/
│   ├── en/ zh-CN/ fr/      long-form documentation
│   ├── report/             2025 report and defence deck
│   ├── archive/            2024 report and research log
│   └── references/         citations and provenance
├── media/
│   ├── photos/project/     v2 renders, v1 build photos, PCB and test views
│   ├── photos/reference/   report figures and key figures
│   ├── gifs/               reference-build demonstrations
│   ├── videos/             original MP4 files
│   └── source/             editable poster files
├── data/                   data and log directory
├── scripts/verify_theory/  pure-Python kinematics and dimensional checks
├── README.md README.zh-CN.md README.fr.md
├── MIGRATION_NOTES.md CHANGELOG.md CONTRIBUTING.md
├── LICENSE.md LICENSE-docs.md
├── .gitignore .gitattributes
└── .github/
```

## Bill of materials

A summary is in [`BOM/onesarm_bom.md`](BOM/onesarm_bom.md); the machine-readable version is [`BOM/onesarm_bom.csv`](BOM/onesarm_bom.csv). Original checklists are under [`BOM/manufacturing/`](BOM/manufacturing/).

### v2 current platform

| Group | v2 items | Quantity |
|---|---|---|
| Long links | X-X and X-Y, 5 mm 5052 aluminium + carbon tube | 4 + 4 |
| Short links | 5 mm 5052 aluminium | 4 |
| Joints | 45° × 1, 90° × 2 | 3 |
| Drive | 42BYGH47 + FLE-42-20, 1:20 | 3 sets |
| Control | STM32F103C8T6 CAN modules + STM32F407ZGT6 controller | 1 set |
| Power | 350 W DC supply, XT60 | 1 |
| Platform | 4040 aluminium profile, three test plates | 1 |
| End effectors | Gripper, ultrasonic, gas sensor, pen | 4 modules |

### v1 reference build

| Group | v1 items | Quantity |
|---|---|---|
| Drive | 15 kgf·cm PWM servo | 3 |
| Controller | Raspberry Pi Pico W | 1 |
| Module boards | Base, Joint A/B, Holder/Sensor, Expand Controller | 5 |
| Interconnect | 16P 2.54 mm gold-finger | As required |
| Printed joints | 9400A resin joint housings | 3 + 3 |

## Getting started

### v2 build

1. **Fabricate the structure.** Use the STEP/STL files in `mechanical/output/`; cut and bend the 5 mm 5052 links, bond the 50 × 46 mm carbon tubes, and print the 9400A joint housings.
2. **Fabricate the electronics.** Order the Gerber archives in `electronics/output/gerber/controller_monitor/` and populate the BOM from `electronics/output/bom/controller_monitor/`.
3. **Assemble the platform.** Build the 4040 frame, fit the 350 W supply, and mount the Controller and Monitor boards.
4. **Configure the control.** Open the STM32CubeIDE projects in `firmware/stm32/` and configure the CAN bus and joint modules for the selected layout.
5. **Run the analysis.** Use the MATLAB scripts in `software/matlab/kinematics/` and the independent Python checks in `scripts/verify_theory/`.

```bash
python scripts/verify_theory/report_checks.py
python -m unittest discover -s scripts/verify_theory -v
```

### v1 reference build

1. Print the v1 joint housings and assemble the five v1 module boards.
2. Order the v1 Gerber archives in `electronics/output/gerber/v1_module_boards/` and build the 16P gold-finger harness.
3. Flash the Pico W with the MicroPython libraries in `firmware/micropython/` and connect the servo rail.

## Demo and testing

The v2 CAD and platform views show the current structure and drive package.

<p align="center">
  <img src="./media/photos/reference/key_figures/fig5-5_working_platform.jpg" alt="v2 arm on the 4040 working platform" width="820"/>
  <br>
  <em><strong>Figure 7 — v2 working platform.</strong> Stepper-driven arm, aluminium/carbon links and the 4040 frame.</em>
</p>

The v1 reference build demonstrations show the servo/Pico reference build in motion, the expand-controller OLED/GNSS display, the gripper/pen module and the simulation view.

<p align="center">
  <img src="./media/gifs/onesarm_motion.gif" alt="v1 reference build arm motion" width="340"/>
  <img src="./media/gifs/onesarm_gripper.gif" alt="v1 reference build gripper demo" width="300"/>
</p>

<p align="center">
  <img src="./media/gifs/onesarm_electronics.gif" alt="v1 reference build OLED and GNSS demo" width="400"/>
  <img src="./media/gifs/onesarm_simulation.gif" alt="Kinematic simulation view" width="400"/>
</p>

<p align="center">
  <img src="./media/photos/project/onesarm_v1_build.jpg" alt="v1 reference build" width="320"/>
  <img src="./media/photos/project/scene_module_assembly_small.jpg" alt="Module assembly view" width="420"/>
  <img src="./media/photos/project/modular_assembly_diagram_small.jpg" alt="24 assembly combinations" width="420"/>
  <br>
  <em><strong>Figure 8 — v1 reference build and assembly views.</strong> The servo/Pico build, a module stack and the 24 permutation/orientation combinations.</em>
</p>

## Design specifications

### v2 current platform

| Parameter | Value | Source |
|---|---|---|
| Analysed configuration | AyCxBy-D, 4 DOF | Report §3.3 |
| Link parameters $d_1, a_2, d_3, a_3, a_4$ | 95, 113.5, 21.34, 88.5, 152 mm | Report Table 3-20 |
| Link-length sum | 354 mm | Computed |
| Maximum model reach | about 450 mm | Computed, 10,000 samples |
| Assemblies | 24 combinations | $3!\,2^{2}$; 24 CAD files |
| Drive | 42BYGH47 + FLE-42-20, 1:20 | Report §5.2.2 |
| Controller | STM32F103C8T6 CAN + STM32F407ZGT6 | Report §5.2.2 / §5.2.3 |
| Platform | 4040 aluminium profile, 350 W supply | Report §5.2.3 |
| Structure | 5 mm 5052 aluminium sheet + 50 × 46 mm carbon tube | Report §5.2.1 |
| FEA material | 9400A resin, $E=2.75$ GPa, $\nu=0.44$, 1150 kg/m³ | Report Table 3-1 |
| FEA load | 10 N at each joint top face | Report §3.1.2 |

### v1 reference build

| Parameter | Value | Source |
|---|---|---|
| Drive | 15 kgf·cm PWM servo, 5–9 V, 180° | Report §2.3.1 |
| Controller | Raspberry Pi Pico W, RP2040 | Report §2.3.2 |
| Module boards | Base, Joint A/B, Holder/Sensor, Expand Controller | Report §2.3.2 |
| Interconnect | 16P 2.54 mm gold-finger | Report §2.3.2 |
| Logic supply | 5 V | Report §2.3.2 |

## Documentation

- [Theory of operation](docs/en/theory_of_operation.md)
- [Mechanical design](docs/en/mechanical_design.md)
- [Electronics and control](docs/en/electronics_and_control.md)
- [Assembly and replication](docs/en/assembly_and_replication.md)
- [Verification](docs/verification.md)
- [Glossary](docs/glossary.md)

Chinese and French versions are in [`docs/zh-CN/`](docs/zh-CN/) and [`docs/fr/`](docs/fr/).

## Contributing

See [`CONTRIBUTING.md`](CONTRIBUTING.md). Add sources and licence notes for third-party figures.

## License

- **Code, firmware and scripts:** [MIT](LICENSE.md).
- **Documentation, original CAD, photos and diagrams:** [CC BY 4.0](LICENSE-docs.md).
- **Third-party figures, papers, videos and trademarks:** excluded from both licences. See [`docs/references/README.md`](docs/references/README.md).

## Acknowledgments

- **Author:** 郭沫晗 (Guo Mohan), Guyuan No. 1 Middle School, Ningxia.
- **Teacher and mentors:** 马博伟 (school robotics studio), 杨旭 (University of Electronic Science and Technology of China), 邵金龙 (Ningxia University), as acknowledged in the report.
- **Competition:** 38th National Youth Science and Technology Innovation Competition (2024).
- **References:** the continuum-robot, modular-arm, mortise-and-tenon and snake-robot literature listed in [`docs/references/README.md`](docs/references/README.md).
- **Tools:** SolidWorks, MATLAB Robotics Toolbox, EasyEDA/LCEDA, STM32CubeIDE, MicroPython, ffmpeg and Pillow.
