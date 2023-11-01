#include <Arduino.h>

class Sensor
{
public:
    Sensor(byte pinSensor, byte pinLed, uint32_t floodLevel, uint32_t detectionDelay)
    {
        _pinLed = pinLed;
        _pinSensor = pinSensor;
        _floodLevel = floodLevel;
        _detectionDelay = detectionDelay;
        _startTime = millis();
        _floodDetected = false;
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
        if (!_floodDetected && getSensorValue() < _floodLevel) {
            // Если сигнал превышает порог, продолжаем отслеживать время
            if (millis() - _startTime >= _detectionDelay) {
                // Если сигнал был выше порога в течение 5 секунд, срабатываем детектор протечек
                _floodDetected = true;

                digitalWrite(_pinLed, HIGH);
            }
        } else {
            // Если сигнал опустился ниже порога, сбрасываем счетчик времени
            _startTime = millis();
        }
    }

    uint32_t getSensorValue()
    {
        return analogRead(_pinSensor);
    }

    bool isFloodDetected()
    {
        return _floodDetected;
    }

private:
    byte _pinLed;
    byte _pinSensor;
    uint32_t _floodLevel;
    uint32_t _detectionDelay;
    unsigned long _startTime;
    bool _floodDetected;
};