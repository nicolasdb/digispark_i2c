#pragma once

#include <stdint.h>

// Minimal stub of TinyWireS to allow compilation in CI/workspace.
// For real hardware use the upstream TinyWireS library available for Digispark.

void TinyWireS_begin(uint8_t addr) __attribute__((weak));
inline void TinyWireS_begin(uint8_t) {}

void TinyWireS_onReceive(void (*)(uint8_t)) __attribute__((weak));
inline void TinyWireS_onReceive(void (*)(uint8_t)) {}

void TinyWireS_onRequest(void (*)(void)) __attribute__((weak));
inline void TinyWireS_onRequest(void (*)(void)) {}

inline bool TinyWireS_available() { return false; }
inline uint8_t TinyWireS_receive() { return 0; }
inline void TinyWireS_send(uint8_t) {}
inline void TinyWireS_stop_check() {}

// Backward-compatible macros used in project
#define TinyWireS TinyWireS
#define TinyWireS.begin TinyWireS_begin
#define TinyWireS.onReceive TinyWireS_onReceive
#define TinyWireS.onRequest TinyWireS_onRequest
#define TinyWireS.available TinyWireS_available
#define TinyWireS.receive TinyWireS_receive
#define TinyWireS.send TinyWireS_send
#define TinyWireS_stop_check TinyWireS_stop_check
