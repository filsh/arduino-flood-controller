#include <Arduino.h>

class Sensor
{
public:
    Sensor(byte pin)
    {
        _pin = pin;
    }

    uint16_t getLevel()
    {
        return analogRead(_pin);
    }

    bool isFlood(uint16_t floodLevel)
    {
        return getLevel() > floodLevel;
    }

private:
    byte _pin;
};