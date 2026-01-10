# Test Checklist — I2C LED Control

1. Physical checks
   - Confirm 12V supply is connected to each board's VIN (if using VIN), and common GND between Nano and all Digisparks.
   - Confirm pull-ups (4.7k) on SDA and SCL to the regulated 5V.

2. I2C Scan
   - Upload slave to a single Digispark with address 0x10.
   - Run `annex_master_example.ino` on Nano and watch serial for device at 0x10.
   - Expected: device found at 0x10.

3. Single slave toggle
   - Use master to send 0x01 to 0x10; LED should turn ON.
   - Send 0x00 to 0x10; LED should turn OFF.
   - Optionally, request status and verify read-back matches the LED.

4. Add additional slaves
   - Add second Digispark at 0x11 and repeat toggles to verify independence.
   - Test toggling both slaves in quick succession.

5. Multi-slave tests
   - Toggle each slave in a sequence; ensure no cross-talk.
   - Confirm I2C scanner finds all assigned addresses.

6. Stress & robustness
   - Rapid toggles (100 ms) for a few minutes; observe stability.
   - Power-cycle a slave while master is running; verify bus recovers and device reappears after reboot.

7. Debugging steps
   - If a slave is not found, verify its VIN, GND, SDA, SCL wiring and address set in the firmware.
   - Use logic analyzer to inspect SDA/SCL if bus errors persist.

8. Safety check
   - Monitor board temperature under expected load; if regulators get hot, migrate to a central 5V buck converter.
