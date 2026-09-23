#include "ArduinoInputOutput.h"

#if defined(ARDUINO)
#include <Arduino.h>

void ArduinoPinCommand::configureInputDigital(uint8_t pin)
{
    pinMode(pin, INPUT);
}

void ArduinoPinCommand::configureInputPullupDigital(uint8_t pin)
{
    pinMode(pin, INPUT_PULLUP);
}

void ArduinoPinCommand::configureOutputDigital(uint8_t pin)
{
    pinMode(pin, OUTPUT);
}

int ArduinoPinCommand::readDigital(uint8_t pin)
{
    return digitalRead(pin);
}

void ArduinoPinCommand::writeDigital(uint8_t pin, uint8_t value)
{
    digitalWrite(pin, value);
}

void ArduinoPinCommand::configureInputAnalog(uint8_t pin)
{
    pinMode(pin, INPUT);
}

void ArduinoPinCommand::configureOutputAnalog(uint8_t pin)
{
    pinMode(pin, OUTPUT);
}

int ArduinoPinCommand::readAnalog(uint8_t pin)
{
    return analogRead(pin);
}

void ArduinoPinCommand::writeAnalog(uint8_t pin, int value)
{
    analogWrite(pin, value);
}

#endif
