"""Regression checks for the OnesArm report review.

Run from the repository root:

    python -m unittest discover -s scripts/verify_theory -v

The tests document both correct maths and known defects. A test named
``..._known_defect`` passes when the defect is still detected; it is not a
statement that the report is correct.
"""

import unittest
from math import pi
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))

from onesarm_model import (  # noqa: E402
    A2, A3, A4, dh_standard, dh_report, fk, position, det3, rotation_orthonormality_error,
    report_eq37_matrix, workspace_bbox, torque_margin, qlim_rad_bug, combination_count,
    count_assembly_models, QLIM_MATLAB_DEG,
)


class TestKinematics(unittest.TestCase):
    def test_standard_dh_is_rigid(self):
        for q in ([0, 0, 0, 0], [0, pi / 2, 0, 0], [0, 0.4, -0.7, 1.1]):
            t = fk(q, dh_standard)
            self.assertLess(rotation_orthonormality_error(t), 1e-12)
            self.assertAlmostEqual(t[3][3], 1.0)
            self.assertAlmostEqual(t[3][0], 0.0)
            self.assertAlmostEqual(t[3][1], 0.0)
            self.assertAlmostEqual(t[3][2], 0.0)

    def test_report_order_is_also_rigid(self):
        t = fk([0, pi / 2, 0, 0], dh_report)
        self.assertLess(rotation_orthonormality_error(t), 1e-12)

    def test_standard_and_report_orders_differ_known_defect(self):
        a = position(fk([0, pi / 2, 0, 0], dh_standard))
        b = position(fk([0, pi / 2, 0, 0], dh_report))
        distance = sum((x - y) ** 2 for x, y in zip(a, b)) ** 0.5
        self.assertGreater(distance, 1e-3)

    def test_eq37_third_column_is_zero_known_defect(self):
        r = [row[:3] for row in report_eq37_matrix(pi / 2)[:3]]
        self.assertAlmostEqual(det3(r), 0.0, places=12)

    def test_tip_reach(self):
        self.assertAlmostEqual(A2 + A3 + A4, 0.354, places=6)


class TestLimitsAndUnits(unittest.TestCase):
    def test_qlim_radian_bug_is_detected(self):
        bug = qlim_rad_bug()
        self.assertGreater(bug["factor"], 50.0)
        self.assertAlmostEqual(bug["intended_range_rad"], pi)

    def test_workspace_bbox_is_finite(self):
        b = workspace_bbox(samples=2000, qlim_deg=QLIM_MATLAB_DEG)
        self.assertLess(b["x_min"], b["x_max"])
        self.assertLess(b["z_min"], b["z_max"])
        self.assertGreater(b["max_reach_m"], 0.0)


class TestLoadAndCombinations(unittest.TestCase):
    def test_servo_margin_known_issue(self):
        m = torque_margin()
        self.assertGreater(m["ratio"], 2.0)

    def test_combination_count(self):
        self.assertEqual(combination_count(3), 24)

    def test_twenty_four_assembly_files(self):
        root = Path(__file__).resolve().parents[2]
        result = count_assembly_models(root)
        self.assertEqual(result["combination_files"], 24)

    @unittest.skip("The report contains no dynamics or quaternion formulation.")
    def test_quaternion_scope(self):
        pass


if __name__ == "__main__":
    unittest.main()
