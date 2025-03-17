#include <jvs_serial.hh>
//#include <jvsio.hh>
#include <queue>

#include "unity.h"

std::queue<u_int8_t> serial1{};
std::queue<u_int8_t> serial2{};

JVSSerial::Interface Uart_1{serial1, serial2};
JVSSerial::Interface Uart_2{serial2, serial1};

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_write(void) {
  //Uart_1.write(0xDE);
  //TEST_ASSERT_EQUAL(Uart_2.read(), 0xDE);
  // test stuff
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_write);
  return UNITY_END();
}

// WARNING!!! PLEASE REMOVE UNNECESSARY MAIN IMPLEMENTATIONS //

/**
 * For native dev-platform or for some embedded frameworks
 */
int main(void) { return runUnityTests(); }
