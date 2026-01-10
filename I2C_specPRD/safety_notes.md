# Safety Notes & Power Guidance ⚠️

- You stated that Nano and Digispark accept 12V on VIN. That uses the onboard regulator to produce 5V for logic and I/O. Verify your board revision's regulator max VIN and thermal limits before sustained operation at 12V.

- Regulator heat: Linear regulators dissipate (Vin - Vout) × I. If many boards draw current, this can cause overheating. For multiple slaves, prefer a single buck regulator (5V) sized for total current and power the boards' 5V pins directly, or power slave 5V rails from the buck while keeping VIN unconnected.

- Grounding: Always use a common ground between master and slaves.

- USB connection: When powering from VIN and also connecting USB, be mindful of possible back-powering paths—verify your board's schematics if you rely on both.

- Fuses & current limiting: If deploying in the field, consider fuses or current limiting for safety.

- Final check: Before connecting multiple slaves, test with one slave and check the board regulator temperature with expected load.
