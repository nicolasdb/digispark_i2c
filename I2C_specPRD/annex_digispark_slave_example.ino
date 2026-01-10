// annex_digispark_slave_example.ino
// TinyWireS-based slave example for Digispark / ATtiny85

#include <TinyWireS.h>

#define I2C_ADDR 0x10
#define LED_PIN 1 // adjust if your board uses a different pin for the LED

volatile uint8_t ledState = 0;

void receiveEvent(uint8_t howMany) {
  while (TinyWireS.available()) {
    uint8_t b = TinyWireS.receive();
    if (b == 1) {
      digitalWrite(LED_PIN, HIGH);
      ledState = 1;
    } else if (b == 0) {
      digitalWrite(LED_PIN, LOW);
      ledState = 0;
    }
  }
}

void requestEvent() {
  TinyWireS.send(ledState);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  TinyWireS.begin(I2C_ADDR);
  TinyWireS.onReceive(receiveEvent);
  TinyWireS.onRequest(requestEvent);
}

void loop() {
  TinyWireS_stop_check(); // allow TinyWireS to handle events
}
