# Wiring Diagram & Notes

## Summary
- Supply: 12V input to VIN on each board (user requirement). Ensure common ground.
- I2C bus uses 5V logic (from each board's regulator). Pull-ups must be tied to the 5V rail.

## Connections
- Nano A4 (SDA)  <-->  Digispark SDA
- Nano A5 (SCL)  <-->  Digispark SCL
- 5V (regulated) <--> pull-up resistors (4.7 kΩ) to SDA and SCL
- GND (common)   <--> all boards

## ASCII diagram (simplified)

  +12V ---+---------------------+------------------+   (to each board VIN)
          |                     |
         [PSU]                 [PSU]
          |                     |
         GND--------------------+------------------(common GND)
                      |
                      |-- Nano VIN (12V)
                      |-- Digispark VIN (12V)

  Nano 5V (regulated) ----+-- 4.7k -- SDA -----------------> to all SDA pins
                          |-- 4.7k -- SCL -----------------> to all SCL pins

## Pull-ups
- Typical: 4.7 kΩ to 5V. If you only have one set of pull-ups already on the bus, do not add more (too many low-value pull-ups reduce signal levels).

## Notes on powering
- If many Digispark slaves are used, feeding each board's VIN at 12V can cause significant heat in linear regulators. Consider a single 5V buck regulator with sufficient current to feed the 5V rails directly to the 5V pin (bypassing onboard regulators) to reduce dissipation.
- Ensure the 5V used for pull-ups is the same regulated 5V used by the boards (i.e., don't pull-up to an external different 5V source unless it shares GND and is at the same voltage).

## Debug tips
- If a device is not found by a scan: check wiring, address, pull-ups, and ensure the slave sketch is running.
- Use a logic analyzer to view SDA and SCL transitions when diagnosing errors.
