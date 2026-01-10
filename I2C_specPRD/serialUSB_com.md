Yes, using `SerialUSB.begin()` with the DigiCDC library **does use pins 3 and 4 (P3 and P4)** on the Digispark ATtiny85, as these pins are internally connected to the USB D+ and D− lines. When USB communication is active, these pins are **not available** for general-purpose I/O or other functions.

Even though the USB signals are routed through the internal USB interface, **P3 (PB3)** and **P4 (PB4)** are physically the USB data pins. Using them for other purposes while `SerialUSB` is active can interfere with USB communication, prevent the device from being recognized, or cause programming issues.

Some key points:
- Pin 3 has a 1.5K pull-up resistor for USB communication, which may affect external circuits.
- You can temporarily free P3 and P4 by calling `SerialUSB.end()`, but you lose USB connectivity.
- After calling `SerialUSB.end()`, you can use them as regular I/O pins, but avoid connecting anything that interferes with USB when reprogramming.
- Re-enable USB with `SerialUSB.begin()` when needed.

For reliable operation, **avoid using pins 3 and 4 for other purposes** if you plan to use `SerialUSB`.

