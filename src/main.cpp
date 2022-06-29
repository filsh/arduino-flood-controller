#include <Arduino.h>
#include "config.h"
#include "timer.h"
#include "alarm.h"
#include "button.h"
#include "sensor.h"
#include "valve.h"

Alarm alarm(PIN_ALARM_LED, PIN_ALARM_BUZZER, 500, 500);

Sensor sensors[] = {
  Sensor(PIN_SENSOR_1),
  Sensor(PIN_SENSOR_2),
  // Sensor(PIN_SENSOR_3),
  // Sensor(PIN_SENSOR_4),
  // Sensor(PIN_SENSOR_5),
  // Sensor(PIN_SENSOR_6),
  // Sensor(PIN_SENSOR_7),
  // Sensor(PIN_SENSOR_8)
};

Valve valves[] = {
  (1)
};

Button btnReset(PIN_BUTTON);
Button btnClose(PIN_BUTTON);
Button btnOpen(PIN_BUTTON);

volatile boolean buttonState = false;

void setup()
{
  Serial.begin(57600);

  alarm.setup();

  pinMode(PIN_RELAY, OUTPUT);
}

void loop()
{
  alarm.loop();

  for (byte i = 0; i < (sizeof(sensors) / sizeof(sensors[0])); i++) {
    if (sensors[i].isFlood(SENSOR_FLOOD_LEVEL)) {
      buttonState = HIGH;

      Serial.print("Flood detected on sensor: [");
      Serial.print(i);
      Serial.print("], level: [");
      Serial.print(sensors[i].getLevel());
      Serial.println("]");
    }
  }

  if (btnReset.click()) {
    buttonState = !buttonState;
  }

  digitalWrite(PIN_RELAY, buttonState);

  if (buttonState) {
    alarm.beep();
  } else {
    alarm.stop();
  }
}
