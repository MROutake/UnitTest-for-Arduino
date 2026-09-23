#pragma once

#include <stdint.h>

class IPinCommand
{
public:
    virtual ~IPinCommand() = default;

    virtual void configureInputDigital(uint8_t pin) = 0;
    virtual void configureInputPullupDigital(uint8_t pin) = 0;
    virtual void configureOutputDigital(uint8_t pin) = 0;
    virtual int readDigital(uint8_t pin) = 0;
    virtual void writeDigital(uint8_t pin, uint8_t value) = 0;

    virtual void configureInputAnalog(uint8_t pin) = 0;
    virtual void configureOutputAnalog(uint8_t pin) = 0;
    virtual int readAnalog(uint8_t pin) = 0;
    virtual void writeAnalog(uint8_t pin, int value) = 0;
};
