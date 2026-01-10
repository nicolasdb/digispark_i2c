#include <Arduino.h>

// Quick blink test for Digispark (ATtiny85)
// On many Digispark boards the onboard LED is wired to P0 (digital 0).
// This example blinks the LED at 250 ms on / 250 ms off.

const uint8_t LED_PIN = 1; // onboard LED (P1)

void setup() {
  // initialize LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Blink LED to visibly show firmware is running
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}
