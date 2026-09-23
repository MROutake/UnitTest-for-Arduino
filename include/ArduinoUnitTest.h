#pragma once

#include "AnalogInputPin.h"
#include "I_InputOutput.h"
#include "PinIO.h"

#if defined(ARDUINO)
#include "ArduinoInputOutput.h"
#else
#include "MockInputOutput.h"
#endif
