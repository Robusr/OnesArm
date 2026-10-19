# Migration notes

## Source and target

- **Source archive:** `F:\Desktop\OnesArm` (left untouched).
- **Target repository:** `F:\Desktop\dev\OnesArm`, branch `chore/repo-organization`.
- The source is not a Git repository; the target was an empty repository with a one-line README.

## What was copied

| New location | Old location | Files |
|---|---|---:|
| `mechanical/source/` | `Drawing/`, `多场景.../图纸/`, `Customized Production/*/SW文件` | 309 |
| `mechanical/output/` | STEP/STL folders, platform, carbon tube, sheet metal | included above |
| `mechanical/analysis/fea/` | `多场景.../分析/力学`, `Drawing/连杆/XY长连杆-静应力分析 1` | images and logs only |
| `electronics/output/` | `Electronic/PCB/`, `多场景.../电子/PCB/` | 22 |
| `firmware/stm32/` | `Control/Hardware/demo/` | 717 |
| `firmware/micropython/` | `多场景.../控制/RPi_pico/` | included above |
| `software/matlab/` | `多场景.../分析/运动学/**/*.m` | 7 |
| `docs/report/` | 2025 report (zh/en), defence deck, novelty report | 5 |
| `docs/archive/` | 2024 report, midterm deck, research log, XMind, related concept | 24 |
| `media/photos/reference/figures/` | `多场景.../演示/论文插图` | 91 |
| `media/photos/reference/board/` | `Presentatiion/展板内容`, `Presentatiion/展板插图` | 25 |
| `media/videos/` | all 11 MP4 files | 11 |
| `BOM/manufacturing/` | `Customized Production/**/*.md/png/pdf` | 14 |

Total copied: **1290 files, 837.7 MB** (including 645 MB media). Sixteen files were skipped as temporary or regenerate output.

## Deliberately not migrated

| Pattern | Reason |
|---|---|
| `*.CWR`, `*.BD2`, `*.BDF`, `*.MFC`, `*.SL4`, `*.BMC` | SolidWorks solver caches; several exceed 100 MB and are regenerable |
| `Debug/`, `.metadata/`, `.settings/`, `*.pdom`, `*.o`, `*.d`, `*.cyclo`, `*.su`, `*.elf`, `*.hex`, `*.map`, `*.list` | IDE/build output |
| `~$*` | Office/SolidWorks lock files |
| `*.zip` inside CAD trees | Zips of folders already present |
| `media/videos/*.mp4` from Git | 509 MB total; three files exceed 100 MB. Kept in the working tree and ignored by Git |
| `media/source/posters/*.psd` from Git | 50 MB of editable poster files; kept locally |

The original archive still contains every skipped file.

## Reference updates

- The old `Presentatiion` spelling is not preserved as a directory; the documents are under `docs/report/` and `docs/archive/`.
- Absolute image paths in the old Markdown (`F:\Desktop\OnesArm\...`, `C:\Users\LEN\Typora\...`) are not used. New documents use relative paths.
- The root README was replaced with the English README; Chinese and French versions are added.
- The 2024 report and the 2025 report are separated, so the 24-combination text and the v2 stepper/CAN chapter are no longer mixed in one undated file.

## Naming

Directories and new files use lowercase `snake_case`. Original Chinese CAD and checklist names are preserved inside the categorized folders for traceability. Fixed top-level README names are `README.md`, `README.zh-CN.md` and `README.fr.md`.

## Large-file policy

- Files under 50 MB may be committed normally.
- CAD/STEP/STL/PDF/PPTX files are committed with `.gitattributes` binary markers.
- Videos and PSD sources are ignored by Git. For a public mirror, publish them as release assets or use Git LFS after checking the total size.
- The repository working tree is about 1.2 GB; the Git index without videos/PSD is much smaller.

## Reproduce the migration

The mapping logic is documented in this file. A reusable copy can be created from the source archive with the same rules; do not delete the source until the target has been verified. The verification commands are in `scripts/verify_theory/README.md`.
