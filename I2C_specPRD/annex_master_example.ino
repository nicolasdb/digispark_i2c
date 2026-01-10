// annex_master_example.ino
// Arduino Nano I2C master example

#include <Wire.h>

void setup() {
  Wire.begin(); // join I2C bus as master
  Serial.begin(115200);
  delay(200);
  Serial.println("Master: ready");
}

void sendLedCmd(uint8_t addr, uint8_t cmd) {
  Wire.beginTransmission(addr);
  Wire.write(cmd);
  uint8_t rc = Wire.endTransmission();
  if (rc == 0) Serial.print("OK to 0x"); else Serial.print("ERR to 0x");
  Serial.println(addr, HEX);
}

uint8_t readLedState(uint8_t addr) {
  Wire.requestFrom((int)addr, 1);
  if (Wire.available()) return Wire.read();
  return 0xFF; // no response
}

void i2cScan() {
  Serial.println("Scanning I2C...");
  for (uint8_t addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found 0x"); Serial.println(addr, HEX);
    }
    delay(5);
  }
}

void loop() {
  i2cScan();

  // Example: toggle 0x10 and 0x11
  sendLedCmd(0x10, 1); // ON
  delay(500);
  sendLedCmd(0x11, 1); // ON
  delay(1000);
  sendLedCmd(0x10, 0); // OFF
  delay(500);
  sendLedCmd(0x11, 0); // OFF
  delay(1000);

  // optional: read back state
  uint8_t s = readLedState(0x10);
  if (s != 0xFF) {
    Serial.print("State 0x10= "); Serial.println(s);
  }

  delay(2000);
}
