#include <jvs_parallel.hh>
#include <vector>

#include "unity.h"

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_parallel_io() {
  // Initialize pin states for testing
  std::vector<uint8_t> pin_states(64, LOW);  // Support up to 64 pins

  // Create interface
  JVSParallel::Interface io(pin_states);

  // Configure pins
  io.pinMode(5, INPUT_PULLUP);

  // Read/write pins
  io.digitalWrite(10, HIGH);
  int value = io.digitalRead(5);
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_parallel_io);
  return UNITY_END();
}

// WARNING!!! PLEASE REMOVE UNNECESSARY MAIN IMPLEMENTATIONS //

/**
 * For native dev-platform or for some embedded frameworks
 */
int main(void) { return runUnityTests(); }
