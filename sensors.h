#include "global_vars.h"
#include "Adafruit_SHTC3.h"

Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();

void setupSensors(){
  Serial.println("SHTC3 init...");
  if (! shtc3.begin()) {
    Serial.println("Couldn't find SHTC3");
    while (1) delay(1);
  }
  Serial.println("Found SHTC3 sensor");
}


void updateBattVolt(){
  int analogValue = analogRead(A0);
  ssBatteryVolt = (analogValue/1023.0) * 3300; // 3300 is the voltage provided by NodeMCU
  Serial.println("Batt Volt: " + String(ssBatteryVolt, 2));
}

void updateTempHumid(){
  sensors_event_t humid, tmp;

  shtc3.getEvent(&humid, &tmp); // populate temp and humidity objects with fresh data
  temp = tmp.temperature;
  humidity = humid.relative_humidity;

  Serial.print("Temperature: " + String(tmp.temperature) + " degrees C");
  Serial.print("Humidity: " + String(humid.relative_humidity) + " % rH");
 
  delay(2000);
}
