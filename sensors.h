#include "global_vars.h"
#include "lib.h"
#include "Adafruit_SHTC3.h"

#define ADC_RATIO (1500 + 220 + 100) / 100 // 1M5 + 220K + 100K

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
  ssBatteryVolt = (analogValue/1024.0) * ADC_RATIO; // 1.0V is the max ADC voltage

  Serial.println("Batt Volt: " + String(ssBatteryVolt, 2));
}

void updateTempHumid(){
  sensors_event_t humid, tmp;

  shtc3.getEvent(&humid, &tmp); // populate temp and humidity objects with fresh data
  temp = tmp.temperature;
  humidity = humid.relative_humidity;

  Serial.println("Temp.: " + String(tmp.temperature) + " degrees C");
  Serial.println("Humidity: " + String(humid.relative_humidity) + " % rH");
 
  delay(100);
}
