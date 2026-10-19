"""Analytical helpers for the OnesArm report review.

All lengths are in metres. Angles are radians unless a function name says
``deg``. Two transform conventions are implemented:

* ``dh_standard``: T = Rot_z(theta) * Trans_z(d) * Trans_x(a) * Rot_x(alpha).
  This is the convention used by Peter Corke's Robotics Toolbox ``Link(...,
  'standard')`` and by the MATLAB scripts in ``software/matlab``.
* ``dh_report``: T = Rot_z(theta) * Rot_x(alpha) * Trans(a, 0, 0) *
  Trans(0, 0, d). This reproduces the homogeneous matrices printed in report
  equations (3.6)-(3.9), where the offset d appears in the x/y translation.

The two conventions are not equivalent. ``docs/errata.md`` records the
difference and its effect on the reported workspace.
"""

from math import cos, sin, pi, sqrt, factorial
from pathlib import Path
import random
import re

# Report Table 3-20, converted from mm to m.
D1 = 0.095
A2 = 0.1135
D3 = 0.02134
A3 = 0.0885
A4 = 0.152

D = [D1, 0.0, D3, 0.0]
A = [0.0, A2, A3, A4]
ALPHA = [pi / 2, pi / 2, pi / 2, 0.0]

# Joint limits. The report table gives (0, 180) for joints 2-4. The MATLAB
# code uses (0, 180), (-90, 90), (-90, 90).
QLIM_REPORT_DEG = [(0, 0), (0, 180), (0, 180), (0, 180)]
QLIM_MATLAB_DEG = [(0, 0), (0, 180), (-90, 90), (-90, 90)]

SERVO_STALL_KGFCM = 15.0
SERVO_STALL_NM = SERVO_STALL_KGFCM * 0.0980665
TIP_REACH_M = A2 + A3 + A4


def mat_mul(a, b):
    rows = len(a)
    cols = len(b[0])
    inner = len(b)
    return [[sum(a[i][k] * b[k][j] for k in range(inner)) for j in range(cols)] for i in range(rows)]


def identity(n=4):
    return [[1.0 if i == j else 0.0 for j in range(n)] for i in range(n)]


def trans(x, y, z):
    t = identity()
    t[0][3], t[1][3], t[2][3] = x, y, z
    return t


def rot_z(theta):
    c, s = cos(theta), sin(theta)
    return [[c, -s, 0.0, 0.0], [s, c, 0.0, 0.0], [0.0, 0.0, 1.0, 0.0], [0.0, 0.0, 0.0, 1.0]]


def rot_x(alpha):
    c, s = cos(alpha), sin(alpha)
    return [[1.0, 0.0, 0.0, 0.0], [0.0, c, -s, 0.0], [0.0, s, c, 0.0], [0.0, 0.0, 0.0, 1.0]]


def dh_standard(theta, d, a, alpha):
    ct, st = cos(theta), sin(theta)
    ca, sa = cos(alpha), sin(alpha)
    return [
        [ct, -st * ca, st * sa, a * ct],
        [st, ct * ca, -ct * sa, a * st],
        [0.0, sa, ca, d],
        [0.0, 0.0, 0.0, 1.0],
    ]


def dh_report(theta, d, a, alpha):
    return mat_mul(mat_mul(mat_mul(rot_z(theta), rot_x(alpha)), trans(a, 0.0, 0.0)), trans(0.0, 0.0, d))


def fk(q, transform=dh_standard):
    t = identity()
    for theta, d, a, alpha in zip(q, D, A, ALPHA):
        t = mat_mul(t, transform(theta, d, a, alpha))
    return t


def position(t):
    return (t[0][3], t[1][3], t[2][3])


def det3(m):
    return (
        m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
        - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
        + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0])
    )


def rotation_orthonormality_error(t):
    r = [row[:3] for row in t[:3]]
    rt = [[r[j][i] for j in range(3)] for i in range(3)]
    p = mat_mul(rt, r)
    return max(abs(p[i][j] - (1.0 if i == j else 0.0)) for i in range(3) for j in range(3))


def report_eq37_matrix(theta):
    """The matrix exactly as printed in report equation (3.7)."""
    c, s = cos(theta), sin(theta)
    return [
        [c, 0.0, 0.0, A2 * c],
        [s, 0.0, 0.0, A2 * s],
        [0.0, 1.0, 0.0, 0.0],
        [0.0, 0.0, 0.0, 1.0],
    ]


def workspace_bbox(qlim_deg=QLIM_MATLAB_DEG, samples=10000, seed=7, transform=dh_standard):
    rng = random.Random(seed)
    pts = []
    for _ in range(samples):
        q = [rng.uniform(lo * pi / 180.0, hi * pi / 180.0) for lo, hi in qlim_deg]
        pts.append(position(fk(q, transform)))
    xs, ys, zs = zip(*pts)
    return {
        "x_min": min(xs), "x_max": max(xs),
        "y_min": min(ys), "y_max": max(ys),
        "z_min": min(zs), "z_max": max(zs),
        "max_reach_m": max(sqrt(x * x + y * y + z * z) for x, y, z in pts),
        "samples": samples,
    }


def torque_margin(load_n=10.0, reach_m=TIP_REACH_M, stall_nm=SERVO_STALL_NM):
    moment = load_n * reach_m
    return {"load_moment_nm": moment, "stall_nm": stall_nm, "ratio": moment / stall_nm}


def qlim_rad_bug():
    # MATLAB: L(3).qlim = [-90 90], without *pi/180.
    return {"interpreted_range_rad": 180.0, "intended_range_rad": pi, "factor": 180.0 / pi}


def combination_count(modules=3):
    return factorial(modules) * (2 ** (modules - 1))


def count_assembly_models(root: Path):
    folder = root / "mechanical/source/assemblies/simplified_24"
    names = [p.name for p in folder.rglob("*.SLDASM")]
    combos = [n for n in names if re.match(r"^[ABC][xy][ABC][xy][ABC][xy]\.SLDASM$", n, re.I)]
    return {"sldasm_total": len(names), "combination_files": len(combos), "names": sorted(combos)}


def main():
    q0 = [0.0, 0.0, 0.0, 0.0]
    q1 = [0.0, pi / 2, 0.0, 0.0]
    print("Standard DH FK q0:", position(fk(q0, dh_standard)))
    print("Report-order FK q0:", position(fk(q0, dh_report)))
    print("Standard DH FK q1:", position(fk(q1, dh_standard)))
    print("Report-order FK q1:", position(fk(q1, dh_report)))
    print("Eq. 3.7 rotation determinant:", det3(report_eq37_matrix(q1[1])))
    print("Workspace bbox (standard DH, MATLAB qlim):", workspace_bbox())
    print("Workspace bbox (report order, MATLAB qlim):", workspace_bbox(transform=dh_report))
    print("Torque margin:", torque_margin())
    print("qlim unit bug:", qlim_rad_bug())
    print("Combination count:", combination_count())
    print("Assembly models:", count_assembly_models(Path(__file__).resolve().parents[2]))


if __name__ == "__main__":
    main()
