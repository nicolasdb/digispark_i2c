#include <Arduino.h>
#include <TinyWireS.h>
#include "i2c_common.h"

#ifndef TARGET_ADDR
#define TARGET_ADDR 0x10
#endif

#define CMD_PING 0x01
#define CMD_PONG 0x02

const uint8_t LED_PIN = 1; // onboard LED (P1)
volatile uint8_t last_cmd = 0;
volatile uint8_t led_duration_units = 0; // units of 10 ms, set by receiveEvent
volatile unsigned long led_on_time = 0;
unsigned long led_timeout_ms = 0;

void receiveEvent(uint8_t howMany) {
  while (TinyWireS.available()) {
    uint8_t b = TinyWireS.receive();
    last_cmd = b;
    // if we receive a ping, set LED and record requested duration unit
    if (b == CMD_PING) {
      // Read optional duration byte if provided
      if (TinyWireS.available()) {
        led_duration_units = TinyWireS.receive();
      } else {
        // default to 1 unit (10 ms) if missing
        led_duration_units = 1;
      }
      digitalWrite(LED_PIN, HIGH); // immediate visual feedback
    }
  }
}

void requestEvent() {
  if (last_cmd == CMD_PING) {
    TinyWireS.send(CMD_PONG);
    last_cmd = 0; // reset
    // do not immediately clear LED; loop() will time it out
  } else {
    TinyWireS.send((uint8_t)0x00);
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Start TinyWireS as a slave at TARGET_ADDR
  TinyWireS.begin(TARGET_ADDR);
  TinyWireS.onReceive(receiveEvent);
  TinyWireS.onRequest(requestEvent);
}

void loop() {
  // Allow TinyWireS to handle I2C events
  TinyWireS_stop_check();

  // If duration was requested, start timer from main context
  if (led_duration_units != 0) {
    led_on_time = millis();
    led_timeout_ms = (unsigned long)led_duration_units * 10UL;
    led_duration_units = 0; // consume
  }

  // turn off LED when timeout expires
  if (led_on_time != 0 && (millis() - led_on_time >= led_timeout_ms)) {
    digitalWrite(LED_PIN, LOW);
    led_on_time = 0;
    led_timeout_ms = 0;
  }
}
