#include "wifi_cloud.h"
#include <CayenneMQTTESP8266.h>


// Name convention: Area_SensorType_Time_Type, ex.: DOOR_MAIN_MINUTES_OPENED, LR_HUMIDITY

#ifndef MY_DEVICES
#define MY_DEVICES

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char dvUsername[] = CAYENNE_USERNAME;
char dvPassword[] = CAYENNE_PASSWORD;
char dvClientID[] = CAYENNE_CLIENT_ID;

#define MESSAGE_DELAY                       100 // millisec
#define MAX_CAYENNE_SIGNAL                  21 // find the last index and update here

#define CH_BATT_VOLTAGE                     1
#define CH_SYSTEM_TIME                      10

#define CH_PS_BATT_VOLTATE                  40
#define CH_PS_RUNTIME                       41   // power station
#define CH_PS_TEMPERATURE                   42
#define CH_PS_HUMIDITY                      43

#define CH_PS_AC_MAIN_DOOR_LIGHT_ON         44   // status

#define CH_PS_AC_MAIN_DOOR_LIGHT            45
#define CH_PS_AC_LED_HEART_MODE             46

// digital states


void cayenneSetup(){
  Serial.println("Cayenne connecting...");
  Cayenne.begin(dvUsername, dvPassword, dvClientID, wifiSsid, wifiPassword);
  Serial.println("Cayenne connected!");
  delay(200);
}

void writeCayenneDigitalState(int channelId, int value){
  delay(MESSAGE_DELAY);
  Cayenne.virtualWrite(channelId, value, "digital_sensor", "d");
}

CAYENNE_OUT_DEFAULT(){
  Cayenne.virtualWrite(CH_PS_BATT_VOLTATE, ssBatteryVolt, "batt", "V");
  Cayenne.virtualWrite(CH_PS_RUNTIME, runtimeMinutes, "counter");
  Cayenne.celsiusWrite(CH_PS_TEMPERATURE, temp);
  Cayenne.virtualWrite(CH_PS_HUMIDITY, humidity, "rel_hum", "p");
  Cayenne.virtualWrite(CH_PS_HUMIDITY, humidity, "rel_hum", "p");
  writeCayenneDigitalState(CH_PS_AC_MAIN_DOOR_LIGHT_ON, mainDoorLightOn);
  Cayenne.virtualWrite(CH_SYSTEM_TIME, systemClock);

  // digital signals

}



#endif
