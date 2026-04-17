#include <Arduino.h>

class Relay
{
public:
    Relay(byte pinRelay, byte pinLed, bool state)
    {
        _pinRelay = pinRelay;
        _pinLed = pinLed;
        _state = state;
    }

    void setup()
    {
        pinMode(_pinRelay, OUTPUT);
        digitalWrite(_pinRelay, _state);
        digitalWrite(_pinLed, _state);
    }

    void loop()
    {
        digitalWrite(_pinRelay, _state);
        digitalWrite(_pinLed, _state);
    }

    void open()
    {
        _state = HIGH;
    }

    void close()
    {
        _state = LOW;
    }

    bool isClosed()
    {
        return _state == LOW;
    }

    bool isOpened()
    {
        return _state == HIGH;
    }

private:
    byte _pinRelay;
    byte _pinLed;
    bool _state = LOW;
};