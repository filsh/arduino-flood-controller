#include <Arduino.h>
#include "config.h"
#include "timer.h"
#include "alarm.h"
#include "button.h"
#include "sensor.h"
#include "relay.h"

Alarm alarm(PIN_ALARM_LED, PIN_ALARM_BUZZER, 500, 200);

Button reset(PIN_BUTTON, 200, 300);
Button open(PIN_BUTTON, 300, 400);
Button close(PIN_BUTTON, 400, 600);

Sensor sensors[] = {
  Sensor(PIN_SENSOR_1, PIN_SENSOR_LED_1, FLOOD_LEVEL),
  Sensor(PIN_SENSOR_2, PIN_SENSOR_LED_2, FLOOD_LEVEL),
  // Sensor(PIN_SENSOR_3, PIN_SENSOR_LED_3, FLOOD_LEVEL),
  // Sensor(PIN_SENSOR_4, PIN_SENSOR_LED_4, FLOOD_LEVEL)
};

Relay relay(PIN_RELAY, RELAY_INITIAL_STATE);

void setup()
{
  Serial.begin(57600);

  alarm.setup();

  relay.open();
  relay.setup();

  for (byte i = 0; i < (sizeof(sensors) / sizeof(sensors[0])); i++) {
    sensors[i].setup();
  }

  Serial.println("Relay open");
}

void loop()
{
  alarm.loop();
  relay.loop();
  
  for (byte i = 0; i < (sizeof(sensors) / sizeof(sensors[0])); i++) {
    Sensor sensor = sensors[i];
    sensor.loop();

    if (sensor.isFlood()) {
      relay.close();
      alarm.beep();

      Serial.print("Flood detected on sensor: [");
      Serial.print(i);
      Serial.print("], level: [");
      Serial.print(sensor.getLevel());
      Serial.println("]");

      Serial.println("Relay close");
    }
  }

  if (reset.click()) {
    Serial.println("Click reset");
    Serial.println("Relay close");
    
    if (relay.getState() != RELAY_INITIAL_STATE) {
      relay.setState(RELAY_INITIAL_STATE);
    }

    for (byte i = 0; i < (sizeof(sensors) / sizeof(sensors[0])); i++) {
      sensors[i].reset();
    }

    alarm.stop();
  }

  if (open.click()) {
    Serial.println("Click open");
    Serial.println("Relay open");

    if (!relay.isOpened()) {
      relay.open();
      alarm.beep();
    }
  }

  if (close.click()) {
    Serial.println("Click close");
    Serial.println("Relay close");

    if (!relay.isClosed()) {
      relay.close();
      alarm.beep();
    }
  }
}
