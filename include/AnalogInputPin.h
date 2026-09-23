#pragma once

#include "PinIO.h"

#include <stdint.h>

class AnalogInputPin
{
public:
    explicit AnalogInputPin(uint8_t pin)
        : pin_(pin)
    {
    }

    void begin() const
    {
        PinIO::configureInputAnalog(pin_);
    }

    int read() const
    {
        return PinIO::readAnalog(pin_);
    }

    uint8_t pin() const
    {
        return pin_;
    }

private:
    uint8_t pin_;
};
