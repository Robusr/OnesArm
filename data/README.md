# Data

The original `Data` folder was empty. No measurement logs, calibration files or test CSVs were found in the archive.

This repository therefore does **not** claim measured payload, repeatability, joint-tracking error, power consumption or mass. The README distinguishes:

- **Reported** — stated in the report (design values or simulation results);
- **Computed** — produced by `scripts/verify_theory/`;
- **Measured** — no such data is present.

## What would make the claims measurable

1. Joint-angle logs from the magnetic encoder or servo feedback during a commanded trajectory.
2. End-effector position measurements (camera or dial gauge) for repeatability.
3. Input power and current logs for the “energy” comparison.
4. Payload tests at a defined reach, with the load location stated.
5. Numerical FEA export (max stress, max displacement, safety factor), not only screenshots.

If you add data, put raw files in `data/raw/`, processed files in `data/processed/`, and document the acquisition conditions in `data/README.md`.
