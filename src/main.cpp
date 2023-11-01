#include <Arduino.h>
#include "config.h"
#include "timer.h"
#include "alarm.h"
#include "button.h"
#include "sensor.h"
#include "relay.h"

Alarm alarm(PIN_ALARM_LED, PIN_ALARM_BUZZER, 500, 200);

Button open(PIN_BUTTON, 300, 400);
Button close(PIN_BUTTON, 400, 600);

Sensor sensors[] = {
  Sensor(PIN_SENSOR_1, PIN_SENSOR_LED_1, FLOOD_LEVEL, SENSOR_DELAY),
  Sensor(PIN_SENSOR_2, PIN_SENSOR_LED_2, FLOOD_LEVEL, SENSOR_DELAY),
  Sensor(PIN_SENSOR_3, PIN_SENSOR_LED_3, FLOOD_LEVEL, SENSOR_DELAY),
  Sensor(PIN_SENSOR_4, PIN_SENSOR_LED_4, FLOOD_LEVEL, SENSOR_DELAY)
};

Relay relay(PIN_RELAY, INITIAL_STATE);

void setup()
{
  Serial.begin(57600);

  alarm.setup();

  relay.setup();
  relay.open();

  for (byte i = 0; i < (sizeof(sensors) / sizeof(sensors[0])); i++) {
    sensors[i].setup();
    alarm.beepOnce();
    delay(300);
  }

  pinMode(PIN_STATE_LED, OUTPUT);

  Serial.println("Setup");
}

void loop()
{
  alarm.loop();
  relay.loop();
  
  for (byte i = 0; i < (sizeof(sensors) / sizeof(sensors[0])); i++) {
    sensors[i].loop();

    if (sensors[i].isFloodDetected()) {
      relay.close();
      alarm.beep();

      Serial.print("Flood detected on sensor: [");
      Serial.print(i);
      Serial.print("], sensor value: [");
      Serial.print(sensors[i].getSensorValue());
      Serial.println("]");

      Serial.println("Relay close");
    }
  }

  if (open.click()) {
    Serial.println("Click open");
    Serial.println("Relay open");

    if (!relay.isOpened()) {
      relay.open();
    }
  }

  if (close.click()) {
    Serial.println("Click close");
    Serial.println("Relay close");

    if (!relay.isClosed()) {
      relay.close();
    }
  }

  digitalWrite(PIN_STATE_LED, relay.getState());
}
