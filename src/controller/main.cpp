#include <Arduino.h>
#include <Wire.h>
#include "i2c_common.h"

#ifndef TARGET_ADDR
#define TARGET_ADDR 0x10
#endif

#define CMD_PING 0x01
#define CMD_PONG 0x02

const uint8_t LED_PIN = 13; // Nano onboard LED (D13)

bool pingTarget(uint8_t addr, uint8_t durationUnits) {
  Wire.beginTransmission(addr);
  Wire.write(CMD_PING);
  Wire.write(durationUnits); // tell target how long to light its LED (units of 10 ms)
  if (Wire.endTransmission() != 0) {
    return false; // no ACK
  }

  delay(10);
  Wire.requestFrom((int)addr, 1);
  if (Wire.available()) {
    uint8_t r = Wire.read();
    return (r == CMD_PONG);
  }
  return false;
}


void setup() {
  Serial.begin(115200);
  while (!Serial) ;
  Serial.println("Controller starting...");
  pinMode(LED_PIN, OUTPUT);
  i2c_init();
  Wire.begin();
}

// Controller-defined duration for target LED (in milliseconds)
const uint16_t TARGET_LED_MS = 150; // change this to implement different scenarios

void loop() {
  uint8_t durationUnits = (uint8_t)((TARGET_LED_MS + 9) / 10); // units of 10 ms, clamped by uint8_t

  // Log the send event with chosen duration
  Serial.print("SENT PING->"); Serial.print(TARGET_ADDR, HEX); Serial.print(" d="); Serial.println(TARGET_LED_MS);

  bool ok = pingTarget(TARGET_ADDR, durationUnits);

  if (ok) {
    // Log the receive event separately
    Serial.print("RECEIVED PONG from "); Serial.print(TARGET_ADDR, HEX); Serial.print(" duration="); Serial.println(TARGET_LED_MS);
    digitalWrite(LED_PIN, HIGH);
    delay(150);
    digitalWrite(LED_PIN, LOW);
  } else {
    Serial.print("NO RESPONSE from "); Serial.println(TARGET_ADDR, HEX);
    // slower blink for failure
    digitalWrite(LED_PIN, HIGH);
    delay(800);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }

  delay(1000);
}
