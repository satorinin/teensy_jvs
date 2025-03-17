#include "jvs_parallel.hh"

namespace JVSParallel {

#ifndef _PLATFORM_TEENSY
Interface::Interface(std::vector<uint8_t>& pin_states)
    : _pin_states(pin_states) {}
#endif

int Interface::digitalRead(uint8_t pin) {
#ifdef _PLATFORM_TEENSY
  return ::digitalRead(pin);
#else
  if (pin < _pin_states.size()) {
    return _pin_states[pin];
  }
  return LOW;
#endif
}

void Interface::digitalWrite(uint8_t pin, uint8_t value) {
#ifdef _PLATFORM_TEENSY
  ::digitalWrite(pin, value);
#else
  if (pin < _pin_states.size()) {
    _pin_states[pin] = value;
  }
#endif
}

void Interface::pinMode(uint8_t pin, uint8_t mode) {
#ifdef _PLATFORM_TEENSY
  ::pinMode(pin, mode);
#else
  // For testing, initialize pin to HIGH if INPUT_PULLUP, LOW otherwise
  if (pin < _pin_states.size()) {
    _pin_states[pin] = (mode == INPUT_PULLUP) ? HIGH : LOW;
  }
#endif
}

}  // namespace JVSParallel
