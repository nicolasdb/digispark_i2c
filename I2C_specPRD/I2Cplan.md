# I2C Plan & Annexes

## Overview ✅
Short: Use an Arduino Nano as the I2C master and multiple Digispark (ATtiny85) boards as I2C slaves. Master will send 1‑byte commands to turn an LED ON (0x01) or OFF (0x00) on each slave. All boards are powered from a 12V supply to their VIN pins (user requirement); notes and mitigations about regulators are included in the Safety Annex.

## Goals 🎯
- Reliable I2C communication between Nano master and multiple Digispark slaves
- Simple, minimal protocol (1-byte commands) for LED control
- Test plan and checklist for verification
- Wiring guide and Bill of Materials for hardware setup

## Assumptions & Power Notes 🔋
- The system will supply 12V to the VIN pins on Nano and Digispark boards (user confirmed). Each board uses its onboard voltage regulator to produce 5V for logic. See `safety_notes.md` for thermal and current considerations.
- I2C runs at standard 100 kHz by default. Pull-ups must be to 5V (the regulated Vcc) so the I2C levels are 5V TTL.

## Hardware & Wiring (summary) 🔧
- Common GND between master and all slaves.
- Connect SDA and SCL lines between master and slaves.
- Use pull-ups on SDA and SCL to the 5V rail (4.7 kΩ recommended).
- Use unique 7-bit addresses per slave (e.g., 0x10, 0x11, 0x12...)
- If powering many slaves from 12V VIN, consider a central 5V buck regulator to power Vcc directly (recommended to reduce heat on board regulators).
- Wiring diagram: see `wiring_diagram.md`.

## Protocol & Addresses 📦
- Command format: single byte
  - 0x00: LED OFF
  - 0x01: LED ON
- Optional: master may request 1 byte from slave (0: OFF, 1: ON) to confirm state.

## Software
- Master (Arduino Nano): use `Wire.h`. Example master sketch: `annex_master_example.ino`.
- Slave (Digispark ATtiny85): use `TinyWireS` (slave). Example slave sketch: `annex_digispark_slave_example.ino`.

## Test Plan & Checklist 🧪
A focused checklist and step-by-step tests are provided in `test_checklist.md`. It covers I2C scanning, per-slave LED toggle tests, multi-slave tests, read-back verification, and stress tests.

## Bill of Materials (short) 🧾
- Arduino Nano (master)
- Digispark / ATtiny85 boards (slaves)
- 4.7 kΩ ×2 pull-up resistors (for SDA/SCL) — shared across bus
- 12V supply (capable of total system current)
- Optional: 5V buck regulator (recommended if many slaves)
- Wires, connectors, and headers
- Optional: logic analyzer / oscilloscope for debugging
Full BOM in `bom.md`.

## Annexes 📎
- `wiring_diagram.md` — wiring notes & ASCII diagram
- `annex_master_example.ino` — Nano master example sketch
- `annex_digispark_slave_example.ino` — Digispark slave example sketch
- `test_checklist.md` — step-by-step test plan and expected results
- `bom.md` — bill of materials
- `safety_notes.md` — power & regulator guidance

---

If you'd like, I can also add PlatformIO example projects for the Nano and for the `digispark-tiny` environment so the code can be built/uploaded directly from this repo. Let me know and I'll add them under `I2C_specPRD/examples/`.
