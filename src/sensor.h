#include <Arduino.h>

class Sensor
{
public:
    Sensor(byte pinSensor, byte pinLed, uint32_t floodLevel)
    {
        _pinLed = pinLed;
        _pinSensor = pinSensor;
        _floodLevel = floodLevel;
    }

    void setup()
    {
        pinMode(_pinLed, OUTPUT);

        digitalWrite(_pinLed, HIGH);
        delay(200);
        digitalWrite(_pinLed, LOW);
    }

    void loop()
    {
        if (isFlood()) {
            digitalWrite(_pinLed, HIGH);
        }
    }

    uint32_t getLevel()
    {
        return analogRead(_pinSensor);
    }

    bool isFlood()
    {
        return getLevel() < _floodLevel;
    }

private:
    byte _pinLed;
    byte _pinSensor;
    uint32_t _floodLevel;
};