# Contributing

Thanks for helping improve OnesArm.

## Ground rules

1. Do not invent measurements. Label every number as **reported**, **computed**
   or **measured**, and link its source.
2. Do not change a formula or conclusion without a derivation, a numerical
   check or a literature reference. Add an entry to `docs/errata.md`.
3. Do not add third-party figures, videos or papers unless the licence allows
   redistribution. Record the source and licence in `docs/references/README.md`.
4. Keep the three READMEs structurally identical. English is the source of
   truth; update Chinese and French in the same pull request.
5. Do not commit raw videos, `.CWR` solver caches or IDE build output. See
   `.gitignore`.

## Commits

Use Conventional Commits, for example:

```text
docs(errata): clarify the DH transform-order mismatch
fix(verification): correct the qlim unit test
feat(firmware): add a minimal PWM servo example
```

## Pull requests

Describe what changed, which evidence supports it, and which checks you ran:

```bash
python scripts/verify_theory/report_checks.py
python -m unittest discover -s scripts/verify_theory -v
```

If a check fails, say so in the pull request. A known failure with an errata
entry is better than a hidden one.
