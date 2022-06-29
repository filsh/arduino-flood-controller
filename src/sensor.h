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
    }

    void reset()
    {
        digitalWrite(_pinLed, LOW);
    }

    void loop()
    {
        _level = analogRead(_pinSensor);

        if (isFlood()) {
            digitalWrite(_pinLed, HIGH);
        }
    }

    int getLevel()
    {
        return analogRead(_pinSensor);
    }

    bool isFlood()
    {
        return _level > _floodLevel;
    }

private:
    byte _pinLed;
    byte _pinSensor;
    uint32_t _level;
    uint32_t _floodLevel;
};