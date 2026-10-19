# Media

```text
media/
├── photos/
│   ├── project/     own renders, prototype photos, PCB renders, test views, GIF posters
│   └── reference/   report figure exports, key figures, poster boards, defence slides
├── gifs/            four README-sized demo GIFs
├── videos/          original MP4 files (not committed; see .gitignore)
└── source/          editable poster files (PSD)
```

## Demo GIFs

| File | Source video | Segment | Size | Dimensions |
|---|---|---|---|---|
| `gifs/onesarm_motion.gif` | `WeChat_20240419013446.mp4` | 15–23 s | 6.6 MB | 400 × 711 |
| `gifs/onesarm_electronics.gif` | `WeChat_20240419013534.mp4` | 2–10 s | 2.4 MB | 400 × 225 |
| `gifs/onesarm_gripper.gif` | `WeChat_20240419013501.mp4` | 4–12 s | 5.4 MB | 360 × 640 |
| `gifs/onesarm_simulation.gif` | `QQ2024419-12239-HD.mp4` | 2–12 s | 0.5 MB | 640 × 399 |

Each GIF has a matching `photos/project/<name>_poster.jpg`. The GIFs are 8 fps, 64-colour palettes, looped, no audio. They are demonstrative recordings, not controlled experiments.

## Original videos

Eleven MP4 files (about 509 MB) are kept in `videos/`. The three largest files (`Video.mp4`, `WeChat_20240419014045.mp4`, `WeChat_20240419013610.mp4`) exceed 100 MB and are deliberately excluded from Git; the working copy is retained locally. The originals also remain in the source archive at `F:\Desktop\OnesArm`.

The videos contain personal workspace views. Review them for private information before publishing a public mirror.

## Figure provenance

See `photos/reference/README.md` and `../docs/references/README.md`. Third-party figures are not covered by the project licences.
