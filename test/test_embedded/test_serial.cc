#include "unity.h"
#include "arduino.h"

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void test_write(void)
{
    // test stuff
}

void test_function_should_doAlsoDoBlah(void)
{
    // more test stuff
}

int runUnityTests(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_write);
    RUN_TEST(test_function_should_doAlsoDoBlah);
    return UNITY_END();
}

// WARNING!!! PLEASE REMOVE UNNECESSARY MAIN IMPLEMENTATIONS //

/**
 * For Arduino framework
 */
void setup()
{
    // Wait ~2 seconds before the Unity test runner
    // establishes connection with a board Serial interface
    delay(2000);

    runUnityTests();
}
void loop() {}