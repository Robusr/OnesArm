# Changelog

All notable changes to OnesArm are documented here. The format follows
[Keep a Changelog](https://keepachangelog.com/en/1.1.0/).

## [1.0.0] — 2026-10-20

### Added

- Organized repository structure: `electronics/`, `mechanical/`, `firmware/`,
  `software/`, `docs/`, `media/`, `BOM/`, `data/` and `scripts/`.
- English, Chinese and French READMEs with a shared structure.
- Long-form documentation: theory, mechanical design, electronics and control,
  assembly and replication.
- `docs/errata.md` with a documented review of the DH convention, matrix
  (3.7), joint limits, combination formula, “energy” index and load case.
- Pure-Python verification scripts and unit tests.
- Consolidated BOM and original manufacturing checklists.
- Four demo GIFs and poster frames, plus a manifest of report figure exports.
- `MIGRATION_NOTES.md` with the old-to-new path map and excluded regenerable
  files.

### Changed

- The 2025-09 report is treated as the canonical text. The 2024 report and
  defence deck are archived under `docs/archive/`.
- Hardware revision v1 (servo + Pico W) and v2 (stepper + CAN) are documented
  separately; the conflict is recorded rather than silently resolved.

### Fixed

- Corrected the third column of report equation (3.7) in the errata, and
  documented the difference between the report transform order and standard
  DH used by MATLAB.
- Corrected the `[-90 90]` joint-limit unit bug in the errata and verification
  script.
- Corrected `kg.cm` torque notation to `kgf.cm` / `N.m`.

### Known issues

- No EDA source files (schematic/PCB project) are present; only Gerber and BOM
  outputs.
- The STM32 projects are CubeMX skeletons; no arm-control firmware is present.
- `Optimization.m` is a MediaPipe pose viewer, not the energy optimisation
  described in the report.
- No measured payload, accuracy, mass or power data exists in the archive.
- The actuator load case (10 N at 0.354 m = 3.54 N.m; up to 4.50 N.m at the
  0.450 m model reach) exceeds one 15 kgf.cm servo’s stall torque (1.47 N.m);
  the load location must be clarified.
