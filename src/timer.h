#include <Arduino.h>

class Timer
{
public:
    Timer(uint16_t period = 0)
    {
        _period = period;
    }
    
    bool ready()
    {
        if (_period && millis() - _timer >= _period) {
            _timer = millis();
            return true;
        }
        return false;
    }

private:
    uint32_t _timer = 0;
    uint16_t _period = 0;
};