# Errata and theory review

## Scope

The OnesArm report is a **statics and kinematics** study of a modular serial arm. It contains no rigid-body dynamics, no quaternion attitude estimator, no IMU fusion and no control-law stability proof. The quaternion and dynamics checklist in the repository prompt is therefore **not applicable**; this document does not invent those sections. The review covers:

- the Denavit–Hartenberg table and homogeneous transforms;
- forward kinematics, joint limits and workspace sampling;
- the modular-combination count;
- the “energy” optimisation index and the load case;
- consistency between the report, the MATLAB scripts, the CAD and the electronics.

All lengths below are in metres unless stated otherwise. Angles are in radians unless marked `deg`.

## Conventions

- **Standard DH** used by Peter Corke’s Robotics Toolbox `Link(..., 'standard')`:
  $$
  T_i = \operatorname{Rot}_z(\theta_i)\,\operatorname{Trans}_z(d_i)\,\operatorname{Trans}_x(a_i)\,\operatorname{Rot}_x(\alpha_i)
  $$
- **Report order** used by equations (3.2)–(3.5):
  $$
  T_i = \operatorname{Rot}_z(\theta_i)\,\operatorname{Rot}_x(\alpha_i)\,\operatorname{Trans}(a_i,0,0)\,\operatorname{Trans}(0,0,d_i)
  $$
  This places the offset $d_i$ along the $y$-axis of the rotated frame, not along $z$. It is a valid rigid transform but **not** standard DH.
- The report’s Table 3-20 uses millimetres; the MATLAB scripts convert to metres. The README uses millimetres for readability and states the unit.

## Errata table

| ID | Location | Original | Type | Status | Correction / evidence |
|---|---|---|---|---|---|
| E-01 | Report Eq. (3.6)–(3.9), p. 33 | Transform order `Rot(z,θ) Rot(x,α) Trans(a,0,0) Trans(0,0,d)` | Kinematics / convention | Confirmed | The printed matrices place $d_1$ and $d_3$ in the $x/y$ translation. Standard DH places $d$ on $z$. The two conventions give different end-effector positions. See `scripts/verify_theory/report_checks.py`. |
| E-02 | Report Eq. (3.7), p. 33 | $T_2^1$ third column printed as `[0, 0, 0]^T` | Kinematics / typo | Confirmed | A rotation block with a zero column has determinant 0, not +1. Under the report’s own order the third column should be `[sin θ₂, -cos θ₂, 0]^T`. The verification test detects the singular matrix. |
| E-03 | Table 3-20, p. 32 vs MATLAB | Table: joints 3 and 4 have range `(0°, 180°)`; MATLAB: `(-90°, 90°)` | Kinematics / data consistency | `[待确认]` | The workspace figures cannot be reproduced until the intended range is confirmed. The README lists both. |
| E-04 | `Simulation_standard.m` line 4 | `L(2)` has `alpha=0` | Kinematics / model error | Confirmed | Table 3-20 and `AyCxBy_D.m` use $\alpha_2=90°$. The standard model uses 90°. |
| E-05 | `Simulation_standard.m` line 5 | `L(3).qlim = [-90 90]` without `*pi/180` | Units | Confirmed | MATLAB reads the range as 180 rad (about 10 313°), not 180°. The factor is 57.3. |
| E-06 | `Simulation_standard.m` lines 24–28 | Workspace formula uses `l(1)`, `l(2)` | Code / reproducibility | Confirmed | `l` is undefined in this script; `aaaa.m` defines `l=[0.457,0.325]`, which does not match the 4-DOF DH model. The workspace section fails or is invalid. |
| E-07 | Report Eq. (3.11), p. 35 | Sum over $i=1..N_{Var}$ of $C_{N_{Var}}^i i! 2^{N_{Var}-1}$ | Combinatorics / notation | Confirmed | For $N_{Var}=3$ the printed sum gives 39, not 24. The report’s Eq. (3.1) and the 24 CAD assemblies use $N_3 = 3!\,2^{3-1}=24$. The general formula needs a corrected derivation. |
| E-08 | Report Eq. (3.28), p. 41; board text | “Energy” = integral of $\lvert\ddot\theta\rvert$; board text uses $\lvert\dot\theta\rvert$ | Optimisation / definition | Confirmed | Neither integral is electrical or mechanical energy: no torque, inertia or efficiency enters. It is a **kinematic effort proxy**. The velocity/acceleration versions also disagree. Call it a proxy, not energy. |
| E-09 | Report §3.1.2–3.1.3, p. 21–28 | 10 N applied to each joint top face; conclusion “can work normally” | Statics / load case | `[待确认]` | 10 N at the 0.354 m link-length reach is 3.54 N·m; at the model’s 0.450 m maximum reach it is 4.50 N·m. One 15 kgf·cm servo stalls at 1.47 N·m (ratios 2.41 and 3.06). The load is applied at joint faces, not necessarily the tip, but the report does not give the load location or a safety factor. |
| E-10 | Report Ch. 2 vs Ch. 5; CAD drive folder | v1: 15 kgf·cm servo + Pico W; v2: 42BYGH47 + FLE-42-20 + STM32 CAN; CAD name `FLE-42-20_42BYGH27` | Configuration control | `[待确认]` | At least two revisions are mixed. The CAD model number 42BYGH27 disagrees with the text 42BYGH47. Freeze one revision before building. |
| E-11 | `firmware/`, report §4.2.3/4.3.1 | Report claims MicroPython open-loop control and kinematics migration | Firmware / evidence | Confirmed gap | The STM32 projects are CubeMX skeletons; CAN is disabled; `keyled.c` has compile errors (`unit32_t`, `uiny32_t`, `HAL_ReadPin`, `tineout`) and `keyled.h` is empty; MicroPython contains only SSD1306 and GNSS libraries. No arm-control `main.py` is present. |
| E-12 | Report §2.3.1, p. 20 | `15kg.cm` | Units / notation | Confirmed | Write `15 kgf·cm` (about 1.47 N·m) or `1.47 N·m`. `kg·cm` is not an SI torque unit. |
| E-13 | Report figures and MATLAB names | `图1-2` repeated; `图4-1` reused; `OnseArm` typo; `AyCyBx-D Workspace` title on an `AyCxBy-D` plot | Documentation | Low severity | Fix labels in the next document revision; no effect on the mechanics. |
| E-14 | `electronics/` | No EDA project or schematic source; only Gerber and BOM | Reproducibility | Confirmed gap | The boards can be fabricated but not edited or regenerated. The original EDA project should be recovered before publication. |
| E-15 | `data/` | Empty in the archive | Evidence | Confirmed gap | No measured payload, repeatability, power or joint-tracking data. All specifications in the README are marked **reported** or **computed**. |

## Impact on conclusions

- The **modular architecture, the T/N mortise-and-tenon interface and the 24-combination count stand.** The 24 assemblies are present as CAD files: 27 SLDASM in `mechanical/source/assemblies/simplified_24`, of which 24 are three-letter combinations and 3 are single-joint models.
- The **printed homogeneous matrices cannot be reproduced as rigid transforms** because of E-02; E-01 means the report and MATLAB use different conventions. Numerical workspace and trajectory values therefore need a decision: adopt standard DH and regenerate the figures, or retain the report order and rewrite the equations and MATLAB model consistently.
- The **“energy” optimisation claim is not supported by the code.** `Optimization.m` is a MediaPipe 3-D pose viewer reading `pose_data_sync.csv`; `energy.m` plots trajectories and workspace but does not compute an energy cost. The report’s proxy should be renamed and implemented explicitly.
- The **10 N load case needs a torque-margin statement.** The FEA mesh images do not show a safety factor in the text.
- The **v2 hardware revision is not a correction of v1**; it is a new platform. The README presents both and marks the conflict.

## Pending questions

1. Which DH convention produced the report’s workspace figures (3-28, 3-29)? The printed matrices and the MATLAB code disagree.
2. Which joint limits are intended for joints 3 and 4: `(0°, 180°)` or `(-90°, 90°)`?
3. Where exactly is the 10 N FEA load applied, and what safety factor is required?
4. Which drive revision is the current one: 42BYGH47 or 42BYGH27?
5. Does the original EDA project exist outside the archive?

## Reproduce this review

```bash
python scripts/verify_theory/report_checks.py > docs/verification_results.txt
python -m unittest discover -s scripts/verify_theory -v
```

Eleven checks run; one quaternion test is skipped because the project has no quaternion formulation. See `docs/verification.md` for the result table.
