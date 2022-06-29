#include <Arduino.h>

class Button
{
public:
    Button(byte pin, uint32_t minValue = 0, uint32_t maxValue = 0)
    {
        _pin = pin;
        _minValue = minValue;
        _maxValue = maxValue;
        pinMode(_pin, INPUT_PULLUP);
    }
    
    bool click()
    {
        uint32_t value = analogRead(_pin);
        bool btnState = value > _minValue && value < _maxValue;

        if (btnState && !_flag && millis() - _tmr >= 100)
        {
            Serial.println(value);
            _flag = true;
            _tmr = millis();
            return true;
        }
        if (!btnState && _flag)
        {
            _flag = false;
            _tmr = millis();
        }

        return false;
    }

private:
    byte _pin;
    uint16_t _tmr;
    uint32_t _minValue;
    uint32_t _maxValue;
    bool _flag;
};