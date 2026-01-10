#include <Arduino.h>
#include "i2c_common.h"

// Controller (Nano) example - previously called "master" in older docs.
// Simple blink of the built-in LED (D13)

const uint8_t LED_PIN = 13; // Nano onboard LED (D13)

void setup() {
  pinMode(LED_PIN, OUTPUT);
  i2c_init();
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
  delay(800);
}
