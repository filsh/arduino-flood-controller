#include <Arduino.h>

class Alarm
{
public:
    Alarm(byte led, byte buzzer, uint16_t frequency = 0, uint16_t duration = 0)
    {
        _led = led;
        _buzzer = buzzer;
        _frequency = frequency;
        _duration = duration;
        _timer = Timer(duration * 2);
    }

    void setup()
    {
        pinMode(_led, OUTPUT);
    }

    void loop()
    {
        if (_state && _timer.ready()) {
            _ledState = _ledState == LOW ? HIGH : LOW;

            tone(_buzzer, _frequency, _duration);
            digitalWrite(_led, _ledState);
        }
    }

    void beep()
    {
        _state = HIGH;
    }

    void beepOnce()
    {
        tone(_buzzer, _frequency, _duration);
        digitalWrite(_led, _ledState);
    }

    void stop()
    {
        _state = LOW;
        _ledState = LOW;

        digitalWrite(_led, _ledState);
    }

private:
    byte _led;
    byte _buzzer;
    Timer _timer;
    uint16_t _frequency;
    uint16_t _duration;
    bool _state = LOW;
    bool _ledState = LOW;
};