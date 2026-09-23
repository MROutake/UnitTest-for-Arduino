#include "PinIO.h"

#if defined(ARDUINO)
#include "ArduinoInputOutput.h"
#else
#include "MockInputOutput.h"
#endif

namespace
{
#if defined(ARDUINO)
    ArduinoPinCommand defaultBackend;
#else
    MockPinCommand defaultBackend;
#endif

    IPinCommand* activeBackend = &defaultBackend;
}

namespace PinIO
{
    IPinCommand& backend()
    {
        return *activeBackend;
    }

    void setBackend(IPinCommand& pinBackend)
    {
        activeBackend = &pinBackend;
    }

    void resetBackend()
    {
        activeBackend = &defaultBackend;

#if !defined(ARDUINO)
        defaultBackend.reset();
#endif
    }

    void configureInputDigital(uint8_t pin)
    {
        backend().configureInputDigital(pin);
    }

    void configureInputPullupDigital(uint8_t pin)
    {
        backend().configureInputPullupDigital(pin);
    }

    void configureOutputDigital(uint8_t pin)
    {
        backend().configureOutputDigital(pin);
    }

    int readDigital(uint8_t pin)
    {
        return backend().readDigital(pin);
    }

    void writeDigital(uint8_t pin, uint8_t value)
    {
        backend().writeDigital(pin, value);
    }

    void configureInputAnalog(uint8_t pin)
    {
        backend().configureInputAnalog(pin);
    }

    void configureOutputAnalog(uint8_t pin)
    {
        backend().configureOutputAnalog(pin);
    }

    int readAnalog(uint8_t pin)
    {
        return backend().readAnalog(pin);
    }

    void writeAnalog(uint8_t pin, int value)
    {
        backend().writeAnalog(pin, value);
    }

#if !defined(ARDUINO)
    MockPinCommand& mock()
    {
        return defaultBackend;
    }
#endif
}
