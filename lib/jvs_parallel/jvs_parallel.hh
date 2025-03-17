#pragma once

#include <cstdint>
#include <vector>

#ifdef _PLATFORM_TEENSY
#include "Arduino.h"
#endif

// Constants to match Arduino's HIGH/LOW
#ifndef _PLATFORM_TEENSY
constexpr int HIGH = 1;
constexpr int LOW = 0;
constexpr int INPUT = 0;
constexpr int OUTPUT = 1;
constexpr int INPUT_PULLUP = 2;
constexpr int INPUT_PULLDOWN = 3;
#endif

namespace JVSParallel {

class Interface {
 public:
#ifdef _PLATFORM_TEENSY
  Interface() = default;
#else
  Interface(std::vector<uint8_t>& pin_states);
#endif

  /// Read the digital value of a pin
  /// @param pin The pin number to read
  /// @return HIGH or LOW
  int digitalRead(uint8_t pin);

  /// Write a digital value to a pin
  /// @param pin The pin number to write to
  /// @param value HIGH or LOW
  void digitalWrite(uint8_t pin, uint8_t value);

  /// Set pin mode
  /// @param pin The pin number to configure
  /// @param mode INPUT, OUTPUT, or INPUT_PULLUP
  void pinMode(uint8_t pin, uint8_t mode);

 private:
#ifndef _PLATFORM_TEENSY
  std::vector<uint8_t>& _pin_states;
#endif
};

}  // namespace JVSParallel
