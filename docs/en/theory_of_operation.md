# Theory of Operation

## 1. Scope

The report is a statics-and-kinematics study. It describes a modular serial arm, enumerates its assembly configurations, builds a 4-DOF Denavit–Hartenberg model, samples the workspace and proposes a cost index for choosing an assembly. It does **not** contain rigid-body dynamics, a quaternion attitude estimator, an IMU or a closed-loop control proof. This document does not add those claims.

## 2. Modular architecture

The arm is divided into:

- a base;
- joint modules (45° and 90° variants);
- link modules (X-X long link, X-Y long link, short link);
- an end-effector module (parallel gripper, ultrasonic probe, gas sensor or pen).

The mechanical interface is a mortise-and-tenon pair inspired by traditional timber joints. The top of a connector carries a “T” node; the bottom carries an “N” node. The N node can slide along the T node in one of two perpendicular directions, so the relative orientation of two modules is selectable. M5 screws clamp the joint.

The report abstracts every connection as a **Connecting Face – Connecting Channel – Connecting Face** (FCF) chain:

![FCF structure](../../media/photos/reference/key_figures/fig5-7_fcf_structure.png)

An X-X or X-Y long link is abstracted as 6 connection faces with 4 channels each; a short link as 4 faces with 4 channels; a joint as 2 faces with 4 channels. Concatenating modules gives a one-dimensional chain of faces and channels:

![Concatenation structure](../../media/photos/reference/key_figures/fig5-8_concat_structure.png)

## 3. Combination count

For the three-module prototype (one 45° module and two 90° modules), the base-adjacent orientation is fixed. The remaining two orientations contribute \(2^2\), and the three modules can be permuted in \(3!\) orders:

\[
N_3 = 3! \cdot 2^{3-1} = 6 \cdot 4 = 24.
\]

The CAD archive contains exactly 24 three-letter combination assemblies plus 3 single-joint models. The report’s general formula (3.11) does not reproduce 24 when evaluated naively; the derivation is recorded in [errata E-07](../errata.md).

## 4. Coordinate frames and DH table

The analysed configuration is **AyCxBy-D**, a 4-DOF chain ending in the parallel gripper. The link frames follow the report’s SDH table:

| \(i\) | \(\theta_i\) | \(d_i\) (mm) | \(a_i\) (mm) | \(\alpha_i\) | Report range |
|---:|---|---:|---:|---:|---|
| 1 | \(\theta_1\) | 95 | 0 | 90° | 0° |
| 2 | \(\theta_2\) | 0 | 113.5 | 90° | 0–180° |
| 3 | \(\theta_3\) | 21.34 | 88.5 | 90° | 0–180° |
| 4 | \(\theta_4\) | 0 | 152 | 0° | 0–180° |

![Link frames](../../media/photos/reference/key_figures/fig3-21_link_frames.png)

The sum of the three link lengths is \(113.5 + 88.5 + 152 = 354\) mm. The full model’s maximum reach is about **450 mm** because the offsets \(d_1\) and \(d_3\) also contribute.

## 5. Transform conventions

The report writes each link transform as

\[
T_i = \operatorname{Rot}_z(\theta_i)\,\operatorname{Rot}_x(\alpha_i)\,
\operatorname{Trans}(a_i,0,0)\,\operatorname{Trans}(0,0,d_i),
\]

which places \(d_i\) in the \(x/y\) translation. Standard DH — the convention used by the MATLAB Robotics Toolbox — is

\[
T_i = \operatorname{Rot}_z(\theta_i)\,\operatorname{Trans}_z(d_i)\,
\operatorname{Trans}_x(a_i)\,\operatorname{Rot}_x(\alpha_i),
\]

which places \(d_i\) on the \(z\)-axis. The two are not equivalent. For example, at \(q=[0,90°,0,0]\) the standard model puts the tool at \((0.021,0,0.449)\) m, while the report-order model gives \((0, -0.074, 0.354)\) m.

Equation (3.7) in the report also prints the third column of \(T_2^1\) as zeros; that block has determinant 0 and cannot be a rotation. Under the report’s own convention the column should be \([\sin\theta_2, -\cos\theta_2, 0]^T\). The full derivation and the numerical check are in [errata E-01/E-02](../errata.md) and [verification](../verification.md).

![MATLAB model](../../media/photos/reference/key_figures/fig3-22_matlab_model.png)

## 6. Forward kinematics and workspace

The forward map is

\[
T_4^0(q) = T_1^0(\theta_1)T_2^1(\theta_2)T_3^2(\theta_3)T_4^3(\theta_4).
\]

With the MATLAB joint limits \((0°,0°)\), \((0°,180°)\), \((-90°,90°)\), \((-90°,90°)\), 10,000 uniformly sampled joint vectors give the following bounding box (standard DH, computed in `scripts/verify_theory/`):

| Axis | Range |
|---|---:|
| x | -0.353 … 0.354 m |
| y | -0.240 … 0.240 m |
| z | -0.076 … 0.449 m |
| maximum reach | 0.450 m |

![Workspace montage](../../media/photos/reference/key_figures/fig3-29_workspaces.png)

The report’s Table 3-20 instead gives \((0°,180°)\) for joints 3 and 4. The MATLAB scripts use \((-90°,90°)\). This conflict changes the envelope and is marked `[待确认]` in the errata. The random-sample box is not a measured workspace or a complete boundary.

## 7. Trajectory planning

The MATLAB scripts use `jtraj`, a quintic polynomial in joint space, and `ctraj` for a Cartesian straight-line path. The report shows position, velocity and acceleration plots for each joint. These are **simulation outputs**, not encoder measurements.

![Trajectory](../../media/photos/reference/key_figures/fig3-27_trajectory.png)

## 8. “Energy” and workspace optimisation

The report proposes

\[
E_{sum} = \sum_{i=1}^{N_{Var}} \int_0^t \left|\ddot{\theta}_i(\tau)\right| d\tau
\]

as an “energy” index. The board text uses the first derivative, \(\left|\dot{\theta}_i\right|\). Neither integral contains torque, inertia or efficiency, so neither is an energy. It is a **kinematic effort proxy**. The archive contains no loop over the 24 assemblies and no implementation of this cost; `Optimization.m` is a MediaPipe pose viewer. The repository therefore labels the method as proposed, not demonstrated. See [errata E-08](../errata.md).

The workspace part compares four assembly modes (AyCxBy-D, AyCyBx-D, AyCxBx-D, AyCyBy-D) and selects the one that best fits a task. The report shows the point clouds but does not give a scalar selection criterion or a measured task trial.

## 9. Statics and finite element analysis

The static study uses 9400A photopolymer resin:

| Property | Value |
|---|---:|
| Young’s modulus | 2.75 GPa |
| Poisson ratio | 0.44 |
| Density | 1150 kg/m³ |
| Tensile strength | 28 MPa |
| Compressive strength | 70 MPa |

![FEA mesh](../../media/photos/reference/key_figures/fig3-2_fea_mesh.png)

Each joint top face is loaded with 10 N; the base is fixed. The report’s conclusion is qualitative: the arm “can work normally” and the displacement is “within the acceptable range”. The text does not give maximum stress, maximum displacement or a safety factor.

A 10 N load at the 354 mm link-length reach is 3.54 N·m; at the 450 mm model reach it is 4.50 N·m. One 15 kgf·cm servo stalls at 1.47 N·m. The load is applied at joint faces rather than at the tip, so this is not a direct tip-load test, but the actuator margin must be stated before the “normal operation” conclusion is accepted. See [errata E-09](../errata.md).

![FEA stress](../../media/photos/reference/key_figures/fig3-5_fea_stress.png)

## 10. What is not modelled

- Rigid-body dynamics, inertia coupling and gravity torque.
- Friction, backlash, compliance and servo dynamics.
- Quaternion attitude estimation or IMU fusion.
- Closed-loop control, PID tuning or stability.
- Measured payload, repeatability, mass or power.

These are legitimate next steps, not hidden results.
