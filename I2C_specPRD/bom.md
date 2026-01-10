# Bill of Materials (BOM)

Core items
- 1 × Arduino Nano (I2C master)
- N × Digispark / ATtiny85 boards (I2C slaves)

Passive & wiring
- 2 × 4.7 kΩ resistors (SDA and SCL pull-ups). If you already have pull-ups on the master or other modules, use only one set.
- Wires, jumpers, headers

Power
- 12V power supply (sized for total system current)
- Optional: 5V buck regulator (recommended for many slaves, to power 5V rail directly)

Tools & debug
- Logic analyzer (optional; helpful for diagnosing I2C issues)
- Multimeter
- USB-serial adapter for master debug via Serial

Notes
- If the system draws significant current, prefer a central buck converter to supply 5V and avoid overheating small linear regulators on VIN pins.