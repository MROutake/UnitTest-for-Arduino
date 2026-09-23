#pragma once

#include "I_InputOutput.h"

#include <stddef.h>
#include <stdint.h>

class MockPinCommand : public IPinCommand
{
public:
    static constexpr size_t MaxPins = 64;

    enum PinMode : uint8_t
    {
        Unconfigured = 0,
        Input = 1,
        InputPullup = 2,
        Output = 3,
        AnalogInput = 4,
        AnalogOutput = 5
    };

    void reset()
    {
        for (size_t pin = 0; pin < MaxPins; ++pin)
        {
            modes_[pin] = Unconfigured;
            digitalValues_[pin] = 0;
            analogValues_[pin] = 0;
        }

        lastConfiguredPin = 0;
        lastDigitalReadPin = 0;
        lastDigitalWritePin = 0;
        lastDigitalWriteValue = 0;
        lastAnalogReadPin = 0;
        lastAnalogWritePin = 0;
        lastAnalogWriteValue = 0;

        configureCallCount = 0;
        digitalReadCallCount = 0;
        digitalWriteCallCount = 0;
        analogReadCallCount = 0;
        analogWriteCallCount = 0;
        outOfRangeAccess = false;
    }

    void configureInputDigital(uint8_t pin) override
    {
        configure(pin, Input);
    }

    void configureInputPullupDigital(uint8_t pin) override
    {
        configure(pin, InputPullup);
    }

    void configureOutputDigital(uint8_t pin) override
    {
        configure(pin, Output);
    }

    int readDigital(uint8_t pin) override
    {
        lastDigitalReadPin = pin;
        ++digitalReadCallCount;

        if (!isValidPin(pin))
        {
            outOfRangeAccess = true;
            return 0;
        }

        return digitalValues_[pin];
    }

    void writeDigital(uint8_t pin, uint8_t value) override
    {
        lastDigitalWritePin = pin;
        lastDigitalWriteValue = value;
        ++digitalWriteCallCount;

        if (!isValidPin(pin))
        {
            outOfRangeAccess = true;
            return;
        }

        digitalValues_[pin] = value;
    }

    void configureInputAnalog(uint8_t pin) override
    {
        configure(pin, AnalogInput);
    }

    void configureOutputAnalog(uint8_t pin) override
    {
        configure(pin, AnalogOutput);
    }

    int readAnalog(uint8_t pin) override
    {
        lastAnalogReadPin = pin;
        ++analogReadCallCount;

        if (!isValidPin(pin))
        {
            outOfRangeAccess = true;
            return 0;
        }

        return analogValues_[pin];
    }

    void writeAnalog(uint8_t pin, int value) override
    {
        lastAnalogWritePin = pin;
        lastAnalogWriteValue = value;
        ++analogWriteCallCount;

        if (!isValidPin(pin))
        {
            outOfRangeAccess = true;
            return;
        }

        analogValues_[pin] = value;
    }

    void setDigitalValue(uint8_t pin, uint8_t value)
    {
        if (!isValidPin(pin))
        {
            outOfRangeAccess = true;
            return;
        }

        digitalValues_[pin] = value;
    }

    void setAnalogValue(uint8_t pin, int value)
    {
        if (!isValidPin(pin))
        {
            outOfRangeAccess = true;
            return;
        }

        analogValues_[pin] = value;
    }

    PinMode getMode(uint8_t pin) const
    {
        if (!isValidPin(pin))
        {
            return Unconfigured;
        }

        return modes_[pin];
    }

    bool isValidPin(uint8_t pin) const
    {
        return pin < MaxPins;
    }

    uint8_t lastConfiguredPin = 0;
    uint8_t lastDigitalReadPin = 0;
    uint8_t lastDigitalWritePin = 0;
    uint8_t lastDigitalWriteValue = 0;
    uint8_t lastAnalogReadPin = 0;
    uint8_t lastAnalogWritePin = 0;
    int lastAnalogWriteValue = 0;

    unsigned int configureCallCount = 0;
    unsigned int digitalReadCallCount = 0;
    unsigned int digitalWriteCallCount = 0;
    unsigned int analogReadCallCount = 0;
    unsigned int analogWriteCallCount = 0;
    bool outOfRangeAccess = false;

private:
    void configure(uint8_t pin, PinMode mode)
    {
        lastConfiguredPin = pin;
        ++configureCallCount;

        if (!isValidPin(pin))
        {
            outOfRangeAccess = true;
            return;
        }

        modes_[pin] = mode;
    }

    PinMode modes_[MaxPins] = {};
    uint8_t digitalValues_[MaxPins] = {};
    int analogValues_[MaxPins] = {};
};

using MockAnalogPin = MockPinCommand;
