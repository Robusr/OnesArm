<p align="center">
  <img src="./media/photos/project/banner.jpg" alt="OnesArm modular serial robotic arm render" width="900"/>
</p>

<h1 align="center">OnesArm</h1>

<p align="center">
  <strong>A reconfigurable modular serial robotic arm for multi-scenario tasks</strong>
  <br>
  24 joint layouts, a mortise-and-tenon interface, and two documented hardware revisions
</p>

<p align="center">
  <a href="./LICENSE.md"><img src="https://img.shields.io/badge/code-MIT-blue.svg" alt="Code: MIT"></a>
  <a href="./LICENSE-docs.md"><img src="https://img.shields.io/badge/docs%20%26%20CAD-CC%20BY%204.0-lightgrey.svg" alt="Docs and CAD: CC BY 4.0"></a>
  <img src="https://img.shields.io/badge/CAD-SolidWorks-e63946" alt="SolidWorks">
  <img src="https://img.shields.io/badge/control-STM32%20%7C%20RP2040-00549f" alt="STM32 and RP2040">
  <img src="https://img.shields.io/badge/status-research%20prototype-orange" alt="Research prototype">
</p>

<p align="center">
  <a href="./README.md">English</a> |
  <a href="./README.zh-CN.md">中文</a> |
  <a href="./README.fr.md">Français</a>
</p>

---

## About the project

**OnesArm** (Chinese project title: 珠联“臂”合) is a modular serial robotic arm built from interchangeable joint, link and end-effector modules. Instead of one fixed kinematic chain, the arm is assembled from standardised **T/N mortise-and-tenon** interfaces. For the three-module prototype, the base-adjacent orientation is fixed and the other two modules each choose one of two perpendicular channels, giving

\[
N_3 = 3! \cdot 2^{3-1} = 24
\]

joint layouts. The 24 assemblies are present as SolidWorks models.

The project was developed by 郭沫晗 (Guo Mohan) at Guyuan No. 1 Middle School, Ningxia. The report describes a first prize at the 38th National Youth Science and Technology Innovation Competition (2024). The repository separates what is **documented**, what is **computed** and what is **not measured**.

> **Two revisions are documented.** v1 uses 15 kgf·cm PWM servos and a Raspberry Pi Pico W. v2 uses 42BYGH47 steppers, FLE-42-20 reducers and an STM32 CAN platform. They are not pin-compatible. Read [`docs/errata.md`](docs/errata.md) before ordering parts.

## Key features

- **24 reconfigurable joint layouts** — three interchangeable modules, two perpendicular channels each, with the base-adjacent orientation fixed.
- **Mortise-and-tenon interface** — a T node on top and an N node below, clamped by an M5 screw; inspired by dovetail and half-lap timber joints.
- **Two documented drive generations** — a low-cost servo/Pico W prototype and a stepper/CAN platform with a 350 W supply.
- **Multi-scenario end effectors** — parallel gripper, HC-SR04 ultrasonic probe, MQ gas sensor and a pen module share the same interface.
- **Open fabrication package** — SolidWorks sources, STEP/STL, Gerber, BOM and manufacturing checklists.
- **Reproducible review** — errata and pure-Python checks for the DH transforms, joint limits, workspace and load case.

## System architecture

```text
                    ┌──────────────────────────────┐
                    │  End effector                │
                    │  gripper / ultrasonic / gas  │
                    └──────────────┬───────────────┘
                                   │ T/N interface
                    ┌──────────────┴───────────────┐
                    │  Link module (XX / XY / short)│
                    └──────────────┬───────────────┘
                                   │
                    ┌──────────────┴───────────────┐
                    │  Joint module (45° / 90°)     │
                    │  drive + bearing + PCB        │
                    └──────────────┬───────────────┘
                                   │
                    ┌──────────────┴───────────────┐
                    │  Base + platform + supply     │
                    └──────────────────────────────┘
```

| Revision | Controller | Drive | Module bus | Supply |
|---|---|---|---|---|
| **v1** | Raspberry Pi Pico W (RP2040, Wi-Fi) | 15 kgf·cm PWM servo | 16P 2.54 mm gold-finger | 5–9 V servo rail |
| **v2** | STM32F103C8T6 CAN modules + STM32F407ZGT6 controller | 42BYGH47 + FLE-42-20 (1:20) | CAN (TJA1050) | 350 W DC, XT60 |

<p align="center">
  <img src="./media/photos/reference/key_figures/fig5-7_fcf_structure.png" alt="Connecting face - connecting channel - connecting face" width="520"/>
  <img src="./media/photos/reference/key_figures/fig5-8_concat_structure.png" alt="Concatenated modular chain" width="520"/>
  <br>
  <em><strong>Figure 1 — FCF abstraction.</strong> Every connection is a connecting face, a connecting channel and another connecting face. Long links have six faces; short links have four; joints have two.</em>
</p>

<p align="center">
  <img src="./media/photos/reference/key_figures/fig5-4_drive_module_render.jpg" alt="Drive module render" width="420"/>
  <img src="./media/photos/project/onesarm_prototype_small.jpg" alt="OnesArm prototype" width="260"/>
  <br>
  <em><strong>Figure 2 — Drive module and prototype.</strong> The 2024 prototype uses printed joint housings, sheet-metal links and a four-suction-cup base. The v2 render shows the stepper/reducer package.</em>
</p>

## Theory and design

### Modular combinations

The report abstracts the chain as **Connecting Face – Connecting Channel – Connecting Face** (FCF). An X-X or X-Y long link has 6 faces × 4 channels; a short link has 4 × 4; a joint has 2 × 4. For the three-module prototype, the 45° module and two 90° modules can be ordered in \(3!\) ways; the base-adjacent orientation is fixed, and the other two orientations give \(2^2\). The result is 24, verified by 24 CAD assemblies plus 3 single-joint models.

### Kinematics

The analysed configuration is **AyCxBy-D**, a 4-DOF chain. Report Table 3-20 gives:

| \(i\) | \(d_i\) (mm) | \(a_i\) (mm) | \(\alpha_i\) | Report range |
|---:|---:|---:|---:|---|
| 1 | 95 | 0 | 90° | 0° |
| 2 | 0 | 113.5 | 90° | 0–180° |
| 3 | 21.34 | 88.5 | 90° | 0–180° |
| 4 | 0 | 152 | 0° | 0–180° |

Standard DH is

\[
T_i = \operatorname{Rot}_z(\theta_i)\,\operatorname{Trans}_z(d_i)\,
\operatorname{Trans}_x(a_i)\,\operatorname{Rot}_x(\alpha_i).
\]

The report prints a different order, \(\operatorname{Rot}_z\operatorname{Rot}_x\operatorname{Trans}(a,0,0)\operatorname{Trans}(0,0,d)\), and Eq. (3.7) has a zero third column. The two conventions give different tool positions. The repository uses standard DH for the verification and records the mismatch in [`docs/errata.md`](docs/errata.md).

<p align="center">
  <img src="./media/photos/reference/key_figures/fig3-29_workspaces.png" alt="Four assembly workspaces" width="760"/>
  <br>
  <em><strong>Figure 3 — Workspace comparison.</strong> Four of the 24 layouts: AyCxBy-D, AyCyBx-D, AyCxBx-D and AyCyBy-D. The plots are simulation samples, not measurements. The random-sample envelope computed from the model is about 0.45 m maximum reach.</em>
</p>

The “energy” index in the report is an integral of joint acceleration (or velocity, in the board text), not electrical energy. It is treated here as a **kinematic effort proxy**, and the repository says so.

## Repository structure

```text
OnesArm/
├── BOM/                    summary + original manufacturing checklists
├── electronics/            Gerber, BOM and silkscreen outputs; no EDA source
├── mechanical/
│   ├── source/             SolidWorks parts and assemblies
│   ├── output/             STEP, STL and fabrication exports
│   └── analysis/fea/       exported FEA images
├── firmware/               STM32 CubeMX projects + MicroPython libraries
├── software/               MATLAB kinematics scripts
├── docs/
│   ├── en/ zh-CN/ fr/      long-form documentation in three languages
│   ├── errata.md           theory and evidence review
│   ├── verification.md     numeric checks and test results
│   ├── report/             canonical 2025 report and defence deck
│   └── archive/            2024 report, research log, related concept
├── media/
│   ├── photos/project/     renders, prototype, PCB and test photos
│   ├── photos/reference/   report figures and key figures
│   ├── gifs/               four demo GIFs
│   ├── videos/             original MP4s (ignored by Git)
│   └── source/             editable poster files (ignored by Git)
├── data/                   no measurement data (documented)
├── scripts/verify_theory/  pure-Python checks and tests
├── README.md README.zh-CN.md README.fr.md
├── MIGRATION_NOTES.md CHANGELOG.md CONTRIBUTING.md
├── LICENSE.md LICENSE-docs.md
├── .gitignore .gitattributes
└── .github/
```

## Bill of materials

A summary is in [`BOM/onesarm_bom.md`](BOM/onesarm_bom.md); the machine-readable version is [`BOM/onesarm_bom.csv`](BOM/onesarm_bom.csv). Original checklists are under [`BOM/manufacturing/`](BOM/manufacturing/).

| Group | Main items | Quantity |
|---|---|---|
| Long links | X-X and X-Y, 5 mm 5052 aluminium + carbon tube | 4 + 4 |
| Short links | 5 mm 5052 aluminium | 4 |
| Joints | 45° × 1, 90° × 2 | 3 |
| v1 drive | 15 kgf·cm PWM servo | 3 |
| v2 drive | 42BYGH47 + FLE-42-20 (1:20) | 3 sets |
| Control | Pico W (v1) or STM32 CAN platform (v2) | 1 set |
| Platform | 4040 aluminium profile, 350 W supply | 1 |
| End effectors | gripper, ultrasonic, gas sensor, pen | 4 modules |

No total mass, payload or measured power is available in the archive.

## Getting started

1. **Choose a revision.** v1 (servo/Pico W) or v2 (stepper/CAN). Do not mix boards.
2. **Build the mechanics.** Print the joint housings, cut/bend the links, bond the carbon tubes and fit the M8/M5 hardware according to [`docs/en/assembly_and_replication.md`](docs/en/assembly_and_replication.md).
3. **Fabricate the electronics.** Order the Gerber archives and populate the BOM. There is no EDA source, so check the board photos before assembly.
4. **Run the analysis.** MATLAB scripts are in `software/matlab/kinematics/`; the independent Python checks are in `scripts/verify_theory/`.
5. **Bring up one joint at a time.** The archived firmware is a skeleton; add the PWM or CAN application for your revision.

```bash
# independent checks (no MATLAB required)
python scripts/verify_theory/report_checks.py
python -m unittest discover -s scripts/verify_theory -v
```

## Demo and testing

The GIFs below are **bench demonstrations**, not controlled experiments. They show the arm moving, the expand-controller OLED/GNSS display, the gripper/pen module and a simulation view. No measured payload or repeatability is claimed.

<p align="center">
  <img src="./media/gifs/onesarm_motion.gif" alt="Arm motion demo" width="360"/>
  <img src="./media/gifs/onesarm_gripper.gif" alt="Gripper demo" width="320"/>
</p>

<p align="center">
  <img src="./media/gifs/onesarm_electronics.gif" alt="Electronics and OLED demo" width="420"/>
  <img src="./media/gifs/onesarm_simulation.gif" alt="Simulation view" width="420"/>
</p>

<p align="center">
  <img src="./media/photos/project/scene_module_assembly_small.jpg" alt="Module assembly" width="420"/>
  <img src="./media/photos/project/modular_assembly_diagram_small.jpg" alt="24 assembly diagram" width="420"/>
  <br>
  <em><strong>Figure 4 — Assembly views.</strong> Left: a module stack. Right: the 24 permutation/orientation combinations used for the assembly study.</em>
</p>

## Design specifications

| Parameter | Value | Source |
|---|---|---|
| Analysed configuration | AyCxBy-D, 4 DOF | Report §3.3 |
| Link lengths \(d_1, a_2, d_3, a_3, a_4\) | 95, 113.5, 21.34, 88.5, 152 mm | Report Table 3-20 |
| Link-length sum | 354 mm | Computed |
| Maximum model reach | about 450 mm | Computed, 10,000 samples |
| Report joint limits | q1 0°, q2–q4 0–180° | Report Table 3-20 |
| MATLAB joint limits | q1 0°, q2 0–180°, q3/q4 ±90° | `software/matlab/kinematics` (conflict) |
| Assemblies | 24 combinations | \(3!\,2^{2}\); 24 CAD files |
| FEA material | 9400A resin, \(E=2.75\) GPa, \(\nu=0.44\), 1150 kg/m³ | Report Table 3-1 |
| FEA load | 10 N at each joint top face | Report §3.1.2 |
| v1 servo | 15 kgf·cm (1.47 N·m) stall, 0.16 s/60° at 6 V | Report §2.3.1 |
| v2 drive | 42BYGH47 + FLE-42-20, 1:20 | Report §5.2.2 |
| Controller | Pico W (v1) / STM32F103 + STM32F407 CAN (v2) | Report §2.3.2 / §5.2.2 |
| Platform | 4040 aluminium profile, 350 W supply | Report §5.2.3 |
| Measured payload, mass, repeatability, power | **Not available** | Archive has no measurement logs |

## Errata and known issues

- Report Eq. (3.7) has a singular rotation block (zero third column).
- The report uses a non-standard DH order; the MATLAB scripts use standard DH. The two give different tool positions.
- Report joint limits for joints 3/4 differ from the MATLAB limits.
- The printed general combination formula (3.11) does not reproduce 24; Eq. (3.1) and the CAD do.
- The “energy” index is a kinematic proxy; `Optimization.m` is a MediaPipe pose viewer, not the optimisation.
- 10 N at 0.354–0.450 m is 3.54–4.50 N·m, above one 15 kgf·cm servo’s 1.47 N·m stall torque.
- The STM32 projects are skeletons; no arm-control firmware or MicroPython `main.py` is present.
- No EDA source, no measured data.

Read [`docs/errata.md`](docs/errata.md) and [`docs/verification.md`](docs/verification.md) for details.

## Roadmap

1. Freeze the hardware revision and resolve 42BYGH27 vs 42BYGH47.
2. Adopt one DH convention, regenerate the figures, and implement the inverse kinematics and the effort proxy over all 24 assemblies.
3. Add a minimal PWM/CAN firmware path and one measured joint-tracking log.
4. Recover the EDA source and publish a fabrication-ready board revision.
5. Measure payload, repeatability, mass and input power at a stated reach.

## Contributing

See [`CONTRIBUTING.md`](CONTRIBUTING.md). Do not add unmeasured numbers or third-party figures without a licence note.

## License

- **Code, firmware and scripts:** [MIT](LICENSE.md).
- **Documentation, original CAD, photos and diagrams:** [CC BY 4.0](LICENSE-docs.md).
- **Third-party figures, papers, videos and trademarks:** excluded from both licences. See [`docs/references/README.md`](docs/references/README.md).

The author should confirm the licence choice before a public release.

## Acknowledgments

- **Author:** 郭沫晗 (Guo Mohan), Guyuan No. 1 Middle School, Ningxia.
- **Teacher and mentors:** 马博伟 (school robotics studio), 杨旭 (University of Electronic Science and Technology of China), 邵金龙 (Ningxia University), as acknowledged in the report.
- **Competition:** 38th National Youth Science and Technology Innovation Competition (2024).
- **References:** the continuum-robot, modular-arm, mortise-and-tenon and snake-robot literature listed in [`docs/references/README.md`](docs/references/README.md).
- **Tools:** SolidWorks, MATLAB Robotics Toolbox, EasyEDA/LCEDA, STM32CubeIDE, MicroPython, ffmpeg and Pillow.
