#include <Arduino.h>

class Sensor
{
public:
    Sensor(byte pin)
    {
        _pin = pin;
    }

    int getLevel()
    {
        return analogRead(_pin);
    }

private:
    byte _pin;
};