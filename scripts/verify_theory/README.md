# Theory verification

Pure-Python checks for the kinematic and dimensional claims in the OnesArm report. No third-party dependency is required.

```bash
python scripts/verify_theory/report_checks.py > docs/verification_results.txt
python -m unittest discover -s scripts/verify_theory -v
```

- `onesarm_model.py` — standard-DH and report-order transforms, workspace sampling, torque and combination checks.
- `test_onesarm_model.py` — regression tests. Tests named `*_known_defect` pass when the documented defect is detected.
- `report_checks.py` — prints the tables copied into `docs/verification.md`.

The project has no dynamics, quaternion or IMU formulation. Quaternion tests are therefore marked as out of scope rather than fabricated.
