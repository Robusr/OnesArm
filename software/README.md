# Software

## MATLAB kinematics

`matlab/kinematics/` contains seven scripts:

| File | Purpose | Status |
|---|---|---|
| `AyCxBy_D.m` | Build the 4-DOF AyCxBy-D model, plot it, open `teach` | Runs if Robotics Toolbox is installed |
| `仿真文件/.../Simulation.m` | Trajectory + workspace plots | Runs |
| `仿真文件/.../energy.m` | Trajectory, Cartesian path, workspace sampling | Runs; does **not** compute energy |
| `仿真文件/.../Simulation_standard.m` | Standard-DH model + workspace | Workspace section fails: `l` is undefined |
| `仿真文件/.../aaaa.m` | SCARA-style 2-link workspace example | Not consistent with the 4-DOF DH model |
| `仿真文件/.../Optimization.m` | MediaPipe 33-landmark 3-D pose viewer | Unrelated to arm optimisation |
| `仿真文件/.../AyCxBy_D.m` | Duplicate of the top-level model with comment edits | Duplicate |

### Known issues

- No `ikine`, `ikcon` or analytical inverse-kinematics implementation is present, although the report claims forward and inverse solutions.
- `Simulation_standard.m` uses `alpha=0` for link 2 and `qlim=[-90 90]` without degree conversion; see `../docs/errata.md` E-04/E-05.
- `Optimization.m` reads `pose_data_sync.csv` (not in the archive) and draws a human skeleton. It is not the energy/workspace optimisation described in §3.4.5.
- The 24 combinations are not enumerated by a script; only the CAD files exist.

### Running

```matlab
addpath(genpath('software/matlab/kinematics'));
AyCxBy_D
```

Requires MATLAB and Peter Corke’s Robotics Toolbox for MATLAB. The scripts use metres; the report table uses millimetres.

## Python verification

The independent checks live in `../scripts/verify_theory/` and use only the Python standard library. They do not require MATLAB.
