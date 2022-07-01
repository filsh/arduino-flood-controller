#include <Arduino.h>

class Sensor
{
public:
    Sensor(byte pinSensor, byte pinCheck, byte pinLed, uint32_t floodLevel)
    {
        _pinLed = pinLed;
        _pinCheck = pinCheck;
        _pinSensor = pinSensor;
        _floodLevel = floodLevel;
    }

    void setup()
    {
        pinMode(_pinLed, OUTPUT);
        pinMode(_pinCheck, INPUT);

        digitalWrite(_pinLed, HIGH);
        delay(200);
        digitalWrite(_pinLed, LOW);

        _connected = digitalRead(_pinCheck);
    }

    void loop()
    {
        if (isFlood() || isBreakLine()) {
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

    bool isBreakLine()
    {
        return isConnected() && digitalRead(_pinCheck) == 0;
    }

    bool isConnected()
    {
        return _connected;
    }

private:
    byte _pinLed;
    byte _pinCheck;
    byte _pinSensor;
    uint32_t _floodLevel;
    bool _connected;
};