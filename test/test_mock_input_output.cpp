#include <unity.h>

#include "ArduinoUnitTest.h"

void test_configures_pin_modes()
{
    MockPinCommand pins;

    pins.configureInputDigital(2);
    pins.configureInputPullupDigital(3);
    pins.configureOutputDigital(4);
    pins.configureInputAnalog(5);
    pins.configureOutputAnalog(6);

    TEST_ASSERT_EQUAL(MockPinCommand::Input, pins.getMode(2));
    TEST_ASSERT_EQUAL(MockPinCommand::InputPullup, pins.getMode(3));
    TEST_ASSERT_EQUAL(MockPinCommand::Output, pins.getMode(4));
    TEST_ASSERT_EQUAL(MockPinCommand::AnalogInput, pins.getMode(5));
    TEST_ASSERT_EQUAL(MockPinCommand::AnalogOutput, pins.getMode(6));
    TEST_ASSERT_EQUAL_UINT(5, pins.configureCallCount);
    TEST_ASSERT_EQUAL_UINT8(6, pins.lastConfiguredPin);
}

void test_reads_configured_analog_value()
{
    MockPinCommand pins;

    pins.setAnalogValue(14, 512);

    TEST_ASSERT_EQUAL(512, pins.readAnalog(14));
    TEST_ASSERT_EQUAL_UINT8(14, pins.lastAnalogReadPin);
    TEST_ASSERT_EQUAL_UINT(1, pins.analogReadCallCount);
}

void test_tracks_digital_writes()
{
    MockPinCommand pins;

    pins.writeDigital(8, 1);

    TEST_ASSERT_EQUAL(1, pins.readDigital(8));
    TEST_ASSERT_EQUAL_UINT8(8, pins.lastDigitalWritePin);
    TEST_ASSERT_EQUAL_UINT8(1, pins.lastDigitalWriteValue);
    TEST_ASSERT_EQUAL_UINT(1, pins.digitalWriteCallCount);
    TEST_ASSERT_EQUAL_UINT(1, pins.digitalReadCallCount);
}

void test_tracks_analog_writes()
{
    MockPinCommand pins;

    pins.writeAnalog(9, 128);

    TEST_ASSERT_EQUAL(128, pins.readAnalog(9));
    TEST_ASSERT_EQUAL_UINT8(9, pins.lastAnalogWritePin);
    TEST_ASSERT_EQUAL(128, pins.lastAnalogWriteValue);
    TEST_ASSERT_EQUAL_UINT(1, pins.analogWriteCallCount);
}

int readSensorRaw(uint8_t pin)
{
    PinIO::configureInputAnalog(pin);
    return PinIO::readAnalog(pin);
}

void test_facade_uses_mock_backend_in_native_tests()
{
    PinIO::resetBackend();
    PinIO::mock().setAnalogValue(14, 777);

    TEST_ASSERT_EQUAL(777, readSensorRaw(14));
    TEST_ASSERT_EQUAL(MockPinCommand::AnalogInput, PinIO::mock().getMode(14));
    TEST_ASSERT_EQUAL_UINT8(14, PinIO::mock().lastAnalogReadPin);
    TEST_ASSERT_EQUAL_UINT(1, PinIO::mock().analogReadCallCount);
}

void test_analog_input_pin_uses_facade_backend()
{
    PinIO::resetBackend();
    PinIO::mock().setAnalogValue(15, 333);

    AnalogInputPin input(15);
    input.begin();

    TEST_ASSERT_EQUAL(333, input.read());
    TEST_ASSERT_EQUAL_UINT8(15, input.pin());
    TEST_ASSERT_EQUAL(MockPinCommand::AnalogInput, PinIO::mock().getMode(15));
}

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    UNITY_BEGIN();
    RUN_TEST(test_configures_pin_modes);
    RUN_TEST(test_reads_configured_analog_value);
    RUN_TEST(test_tracks_digital_writes);
    RUN_TEST(test_tracks_analog_writes);
    RUN_TEST(test_facade_uses_mock_backend_in_native_tests);
    RUN_TEST(test_analog_input_pin_uses_facade_backend);
    return UNITY_END();
}
