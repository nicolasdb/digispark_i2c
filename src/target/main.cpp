#include <Arduino.h>
#include "i2c_common.h"

// Target (Digispark ATTiny85) example - previously called "slave" in older docs.
// Quick blink test to show firmware is running.

const uint8_t LED_PIN = 1; // onboard LED (P1)

void setup() {
  // initialize LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  i2c_init();
}

void loop() {
  // Blink LED to visibly show firmware is running
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}
