# Verification

## Environment and commands

- Python 3.11.9, standard library only.
- Run from the repository root:

```bash
python scripts/verify_theory/report_checks.py > docs/verification_results.txt
python -m unittest discover -s scripts/verify_theory -v
```

## Test summary

```text
Ran 11 tests in 0.117s
OK (skipped=1)
```

- **10 passed**, **0 failed**, **1 skipped**.
- The skipped test is `test_quaternion_scope`: the report contains no quaternion, IMU or attitude-estimation formulation. No quaternion tests were fabricated.

## Forward kinematics

The two transform conventions give different positions for the same joint vector. Lengths in metres.

| Configuration | Standard DH position | Report-order position |
|---|---|---|
| q = [0, 0, 0, 0] | (0.354, 0.000, 0.07366) | (0.354, -0.07366, 0.000) |
| q = [0, 90, 0, 0] deg | (0.02134, 0.000, 0.44900) | (0.000, -0.07366, 0.35400) |
| q = [0, 45, -30, 30] deg | (0.283892, 0.110068, 0.241232) | (0.261257, 0.033549, 0.153777) |

The difference is not rounding: the report places $d_1$ and $d_3$ after the $x$-rotation, so the offset appears in the $x/y$ translation. Standard DH keeps $d$ on the $z$-axis. See `errata.md` E-01.

## Report equation (3.7)

The printed $T_2^1$ rotation block has a zero third column. Its determinant at $\theta_2=90°$ is:

```text
det(R) = 0.000000
```

A rigid rotation requires $\det(R)=+1$. Under the report’s own transform order the third column should be $[\sin\theta_2, -\cos\theta_2, 0]^T$. The verification test records this as a known defect (E-02).

## Workspace sampling

10,000 random joint samples, standard DH, MATLAB joint limits:

| Quantity | Value |
|---|---:|
| x range | -0.3533 … 0.3538 m |
| y range | -0.2405 … 0.2404 m |
| z range | -0.0759 … 0.4488 m |
| maximum reach | 0.4496 m |

Report-order transforms with the same limits give a different box (`x` -0.3545 … 0.3519, `y` -0.3353 … 0.1464, `z` -0.1501 … 0.3533), confirming that the printed matrices and the MATLAB model are not the same model.

The report’s Table 3-20 gives `(0°, 180°)` for joints 3 and 4, while the MATLAB code uses `(-90°, 90°)`. A second sampling run with the report limits is included in `verification_results.txt`; it changes the box but not the conclusion.

This is a **model-derived random-sample envelope**, not a measured workspace and not a complete boundary. The report figures show a much narrower point cloud; the sampling method behind those figures is not documented, so the difference is marked `[待确认]`.

## Actuator load case

- Link-length sum $a_2+a_3+a_4 = 0.354$ m.
- 10 N at 0.354 m: **3.540 N·m**.
- 10 N at the model’s 0.4496 m maximum reach: **4.496 N·m**.
- One 15 kgf·cm servo stall torque: **1.471 N·m**.
- Load / stall ratio: **2.41** at 0.354 m; **3.06** at 0.4496 m.

Both exceed a single servo’s stall torque. The FEA applies 10 N at each joint top face, not necessarily at the tip, and the report does not state the load location or a safety factor. The margin is therefore unresolved, not “passed”. See `errata.md` E-09.

## Joint-limit units

`Simulation_standard.m` line 5 uses `qlim=[-90 90]` without `*pi/180`. MATLAB reads this as 180 rad (about 10,313°), a factor of **57.3** too large. The correct range is $\pi$ rad. See E-05.

## Assembly count

- Combinatorial count for three interchangeable modules with the base-adjacent orientation fixed:
  $$
  N_3 = 3! \cdot 2^{3-1} = 24.
  $$
- CAD inventory: **27 SLDASM** in `mechanical/source/assemblies/simplified_24`, of which **24** are three-letter combinations and **3** are single-joint models.
- The printed general formula (3.11) does not reproduce 24 for $N=3$; see E-07.

## What was not verified

- No dynamics, quaternion, IMU, PID or stability analysis exists in the report or code.
- No measured joint tracking, payload, repeatability, mass or power data exists in the archive.
- The report’s numerical workspace figures could not be reproduced from the printed matrices; they are consistent with a standard-DH model but the generating script and joint ranges are not documented.
- The 24-combination count is verified from the CAD files, not by an executable enumeration script.

## Result

The structural concept and the 24-combination inventory are supported by the archive. The printed kinematics contain a singular matrix and a convention mismatch; the “energy” optimisation is a kinematic proxy without an implementation. The repository documents these limitations instead of hiding them.
