#include <Arduino.h>

class Button
{
public:
    Button(byte pin)
    {
        _pin = pin;
        pinMode(_pin, INPUT_PULLUP);
    }
    
    bool click()
    {
        bool btnState = digitalRead(_pin);
        if (!btnState && !_flag && millis() - _tmr >= 100)
        {
            _flag = true;
            _tmr = millis();
            return true;
        }
        if (btnState && _flag)
        {
            _flag = false;
            _tmr = millis();
        }
        return false;
    }

private:
    byte _pin;
    uint16_t _tmr;
    bool _flag;
};