# ArduinoUnitTest

Kleine Hardware-Abstraktion fuer Arduino-Pins, damit Sensor-Code in Unity-Tests
gegen einen Mock laufen kann und auf dem Board die echten `Arduino.h`-Funktionen
verwendet.

## Grundidee

Produktivcode ruft nur die `PinIO`-Funktionen auf. Im Arduino-Build verwendet
`PinIO` dahinter `ArduinoPinCommand`, im Native-/Unity-Test automatisch den
globalen `MockPinCommand`.

```cpp
#include "ArduinoUnitTest.h"

int readSensorRaw(uint8_t pin)
{
    PinIO::configureInputAnalog(pin);
    return PinIO::readAnalog(pin);
}
```

Oder als Pin-Objekt in einer Sensor-Klasse:

```cpp
#include "ArduinoUnitTest.h"

class AnalogSensor
{
public:
    explicit AnalogSensor(uint8_t pin)
        : input_(pin)
    {
    }

    void begin()
    {
        input_.begin();
    }

    int read()
    {
        return input_.read();
    }

private:
    AnalogInputPin input_;
};
```

```cpp
PinIO::resetBackend();
PinIO::mock().setAnalogValue(14, 512);

TEST_ASSERT_EQUAL(512, readSensorRaw(14));
```

## Lokal testen

```sh
/home/theo/.platformio/penv/bin/pio test -e native
```
