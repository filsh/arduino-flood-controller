#include <Arduino.h>

class Relay
{
public:
    Relay(byte pin, bool state)
    {
        _pin = pin;
        _state = state;
    }

    void setup()
    {
        pinMode(_pin, OUTPUT);
        digitalWrite(_pin, _state);
    }

    void loop()
    {
        digitalWrite(_pin, _state);
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

    bool getState()
    {
        return _state;
    }

    void setState(bool state)
    {
        _state = state;
    }

private:
    byte _pin;
    bool _state = LOW;
};