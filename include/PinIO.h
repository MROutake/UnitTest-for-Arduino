#pragma once

#include "I_InputOutput.h"

#include <stdint.h>

#if !defined(ARDUINO)
#include "MockInputOutput.h"
#endif

namespace PinIO
{
    IPinCommand& backend();
    void setBackend(IPinCommand& pinBackend);
    void resetBackend();

    void configureInputDigital(uint8_t pin);
    void configureInputPullupDigital(uint8_t pin);
    void configureOutputDigital(uint8_t pin);
    int readDigital(uint8_t pin);
    void writeDigital(uint8_t pin, uint8_t value);

    void configureInputAnalog(uint8_t pin);
    void configureOutputAnalog(uint8_t pin);
    int readAnalog(uint8_t pin);
    void writeAnalog(uint8_t pin, int value);

#if !defined(ARDUINO)
    MockPinCommand& mock();
#endif
}
