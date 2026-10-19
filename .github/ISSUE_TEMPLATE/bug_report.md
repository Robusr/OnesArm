---
name: Bug report
about: Report a documentation, CAD, firmware or verification problem
title: "[bug] "
labels: bug
assignees: ""
---

## What is wrong?

Describe the problem and the file/line.

## Expected behaviour

What should happen instead?

## Evidence

Paste the command, output or screenshot. If a number is involved, state whether it is reported, computed or measured.

## Checks run

- [ ] `python scripts/verify_theory/report_checks.py`
- [ ] `python -m unittest discover -s scripts/verify_theory -v`
- [ ] Link/path check on the touched Markdown

## Additional context

Do not include private workspace photos, credentials or third-party copyrighted material.
