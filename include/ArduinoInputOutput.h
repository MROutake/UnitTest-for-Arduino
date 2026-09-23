#pragma once

#include "I_InputOutput.h"

#if defined(ARDUINO)

class ArduinoPinCommand : public IPinCommand
{
public:
    void configureInputDigital(uint8_t pin) override;
    void configureInputPullupDigital(uint8_t pin) override;
    void configureOutputDigital(uint8_t pin) override;
    int readDigital(uint8_t pin) override;
    void writeDigital(uint8_t pin, uint8_t value) override;

    void configureInputAnalog(uint8_t pin) override;
    void configureOutputAnalog(uint8_t pin) override;
    int readAnalog(uint8_t pin) override;
    void writeAnalog(uint8_t pin, int value) override;
};

using ArduinoAnalogInput = ArduinoPinCommand;

#endif
