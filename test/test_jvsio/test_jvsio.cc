#include <jvs_parallel.hh>
#include <jvs_serial.hh>
#include <jvsio.hh>
#include <queue>
#include <vector>

#include "unity.h"

std::queue<u_int8_t> serial1{};
std::queue<u_int8_t> serial2{};

JVSSerial::Interface Uart_1{serial1, serial2};
JVSSerial::Interface Uart_2{serial2, serial1};

// Test fixture
std::vector<uint8_t> pin_states(64, LOW);  // Support 64 pins
JVSParallel::Interface parallel(pin_states);
JVSConfig test_config;

void setUp(void) {
  // Reset pin states
  std::fill(pin_states.begin(), pin_states.end(), LOW);

  // Create test configuration
  test_config.test_button = 41;
  test_config.service_button = 42;

  // Player 1 config
  PlayerConfig player1;
  player1.buttons = {7, 8, 9, 10, 11, 12, 28, 29};
  player1.levers = {5, 4, 22, 6};
  player1.start_button = 36;
  test_config.players.push_back(player1);

  // Player 2 config
  PlayerConfig player2;
  player2.buttons = {21, 20, 19, 18, 40, 39, 38, 37};
  player2.levers = {31, 30, 32, 23};
  player2.start_button = 35;
  test_config.players.push_back(player2);
}

void tearDown(void) { test_config.players.clear(); }

void test_setup_io() {
  JVSIO jvs(parallel, test_config);
  jvs.setup_io(test_config);

  // Verify all pins are configured as INPUT_PULLUP
  for (const auto& player : test_config.players) {
    // Test start button
    TEST_ASSERT_EQUAL(HIGH, pin_states[player.start_button]);

    // Test lever pins
    for (const auto& lever_pin : player.levers) {
      TEST_ASSERT_EQUAL(HIGH, pin_states[lever_pin]);
    }

    // Test button pins
    for (const auto& button_pin : player.buttons) {
      TEST_ASSERT_EQUAL(HIGH, pin_states[button_pin]);
    }
  }
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_setup_io);
  return UNITY_END();
}

int main(void) { return runUnityTests(); }
