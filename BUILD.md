# Build & Upload

This project uses a single repo with multiple PlatformIO environments (one per board). Sources are organized under `src/`:

- `src/common/` — shared code
- `src/controller/` — Nano (controller) firmware (previously `master`)
- `src/target/` — Digispark (target) firmware (previously `slave`)

Header(s) that should be visible to all builds live in `include/`.

Common commands:

- Build Nano (controller):

  pio run -e nano

- Upload Nano:

  pio run -e nano -t upload

- Build Digispark (target):

  pio run -e digispark-tiny

- Upload Digispark (uses Digispark uploader):

  pio run -e digispark-tiny -t upload

Notes:
- The `platformio.ini` uses `build_src_filter` to select which sources are compiled for each environment.
- Build flags now use `-DROLE_CONTROLLER` and `-DROLE_TARGET`.
- Add per-env `lib_deps` or `upload_port` in `platformio.ini` as needed.
