Upload to Digispark with VSCode and PlatformIO

To upload code to a Digispark using VSCode and PlatformIO, follow these steps:

1. Install the PlatformIO extension for VSCode if not already installed.
2. Create a new project or open an existing one, ensuring the `platformio.ini` file is configured correctly for the Digispark. The minimal configuration is:
   ```ini
   [env:digispark-tiny]
   platform = atmelavr
   board = digispark-tiny
   framework = arduino
   ```
   This setup uses the default `micronucleus` upload protocol, which is automatically selected by PlatformIO for the Digispark board 

3. Install the necessary drivers. If using Windows, install the Digistump drivers from the PlatformIO package directory: `C:\Users\<user>\.platformio\packages\tool-micronucleus\Digistump_Drivers`  On Linux or macOS, ensure the `micronucleus` tool is properly installed via the system package manager or PlatformIO's package manager.

4. Prepare the Digispark for upload. The device must be unplugged before starting the upload process. When the upload command is executed, PlatformIO will prompt you to plug in the device within a 60-second timeout 

5. Execute the upload command. In VSCode, use the command palette (`Ctrl+Shift+P`) and select "PlatformIO: Upload" or run the command `pio run -t upload` in the terminal  The system will compile the code and then wait for the device to be connected.

6. Plug in the Digispark into a USB port when prompted. The device will briefly appear in the device manager as "libusb-win32 Digispark Bootloader" (on Windows) or as a serial device (on Linux/macOS), but only for a few seconds before exiting bootloader mode  It is crucial to plug it in only after the upload command starts and to unplug it before the next upload.

7. If the upload fails due to an outdated `micronucleus` version (common with newer Digispark boards), you may need to build a newer version of the `micronucleus` tool. For example, on Ubuntu or Debian, you can build it from source and then configure PlatformIO to use the custom version by setting `upload_protocol = custom` and defining `upload_command` in `platformio.ini` 

8. After successful upload, the Digispark will automatically restart and run the uploaded code.

Quick blink test: A minimal blink sketch is included in `src/main.cpp` — after uploading the firmware the onboard LED (P0) should blink (~250 ms on, 250 ms off). To upload verbosely use:

```bash
pio run -t upload -e digispark-tiny -v
```


Note: Some users have reported that the Digispark only connects reliably through a USB hub on Windows, not directly on certain ports, so try a different USB port or hub if the device is not detected 


---

To manage `micronucleus` on Fedora Kinoite for Digispark programming:

1. **Install Dependencies**: Fedora Kinoite uses `rpm-ostree`, so install required packages via `rpm-ostree install libusb1-devel make git`. Reboot to apply changes.

2. **Build micronucleus**: Clone and compile the tool:
   ```bash
   git clone https://github.com/micronucleus/micronucleus.git
   cd micronucleus/commandline
   make
   sudo make install
   ```

3. **PlatformIO Configuration**: In VSCode with PlatformIO, use this `platformio.ini`:
   ```ini
   [env:digispark-tiny]
   platform = atmelavr
   board = digispark-tiny
   framework = arduino
   ```
   PlatformIO automatically uses `micronucleus`; avoid manually setting `upload_protocol` to prevent conflicts.

4. **Upload Workflow**: Unplug the Digispark, start upload in VSCode, then plug in the device when prompted.

---

why digispark? 

the Digispark (Attiny85-based) can be powered directly from 7–35V (12V recommended) via its VIN pin, thanks to an onboard 5V linear regulator (e.g., 78M05), making it more robust for 12V systems like automotive or industrial applications.


Yes, the **Digispark (ATtiny85)** is a **good choice** for controlling a **12V solenoid valve via MOSFET** over **I2C** in a **multi-node setup** (1 master, multiple slave modules), especially when:

- **Native 12V operation** is required — the Digispark can be powered directly from 12V via its onboard 5V regulator.
- **Low cost and small size** matter — Digispark is compact and inexpensive.
- **Simple I2C slave functionality** is sufficient — using **TinyWireS**, it can act as an I2C slave to receive commands (e.g., "turn on valve X").

Each Digispark can drive one MOSFET (e.g., IRLZ44N or logic-level MOSFET), which switches the 12V solenoid. A flyback diode across the solenoid coil is essential to suppress inductive kickback.

The **ESP32-C3 or Arduino Nano** can act as the **I2C master**, sending commands to multiple Digispark slaves (each with a unique I2C address) to control individual valves.

While the ESP32-C3 is more powerful, it **cannot natively handle 12V**, so using it directly in 12V systems requires additional voltage regulation. The Digispark’s built-in 5V regulator gives it an edge in such environments.

Thus, for **robustness, simplicity, and native 12V support**, the **Digispark is a solid choice** as an I2C-controlled valve driver node.

---

I2C address setting

To set individual I2C addresses for multiple Digispark (ATtiny85) modules, define a unique 7-bit slave address for each device in the code using the TinyWireS.begin(address) function

you can design a custom PCB or modify the setup to support hardware-based I2C address selection:

Solder Pads: Add pads connected to GPIO pins or unused lines that can be shorted to VCC or GND to set different address bits. For example, use two GPIOs to read pad states (open, shorted to VCC/GND) and configure I2C_SLAVE_ADDR accordingly in code.
DIP/Microswitch Array: Connect small switches to GPIO pins to manually select addresses. Each switch combination can represent a binary value used to compute the final I2C address at startup.
Resistor Ladder or Jumper Pins: Use configurable jumpers or resistors to set logic levels on input pins, which the firmware reads to determine the address.
This approach is common with I2C devices like sensors or port expanders (e.g., PCF8575), where A0, A1, A2 pads allow 8 possible addresses.

a 7-position DIP switch can cover the full 7-bit I2C address range (0x00 to 0x7F), as each switch represents one bit. However, practical limitations apply:

Reserved addresses: Some 7-bit values (e.g., 0x00, 0x78–0x7F) are reserved for special purposes (general call, high-speed mode), so usable addresses are typically 0x08 to 0x77.
ATtiny85 GPIO limits: The Digispark (ATtiny85) has only 5 usable GPIO pins, making a full 7-bit DIP switch impractical without external logic or shift registers.
Firmware implementation: You’d read the switch states at startup and set TinyWireS.begin(address) accordingly.
Thus, while theoretically possible, a 7-bit DIP switch is not practical on Digispark. A 3–4 bit switch (supporting 8–16 addresses) is more feasible and sufficient for most applications.

---

Instead of using DIP switches or solder pads, you can use the rotary switch to select one of 16 physical positions, each corresponding to a unique 4-bit binary value. These 4 bits can be read by the ATtiny85 (Digispark) via GPIO pins and combined with a base I2C address to assign a unique slave address (e.g., base 0x10 + rotary position)
https://nl.aliexpress.com/item/1005009441926138.html
