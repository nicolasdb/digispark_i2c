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

Ping test and address notes:

- By default both envs use `TARGET_ADDR=0x10` (set at build time in `platformio.ini`).
  You can change that per-env by editing `platformio.ini` (e.g. `-DTARGET_ADDR=0x11`) or add extra envs for different addresses.

- How the ping test works:
  - Controller writes `0x01` (PING) to the target address, then requests 1 byte.
  - Target replies with `0x02` (PONG) when it sees a PING.

Notes:
- The `platformio.ini` uses `build_src_filter` to select which sources are compiled for each environment.
- Build flags now include `-DTARGET_ADDR=<addr>` so you can define addresses at build time.
- On Digispark targets we use `TinyWireS` as the I2C slave implementation.
