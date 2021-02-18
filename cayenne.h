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
#define CH_BM_RUNTIME                       2 // basement node
#define CH_BM_TEMPERATURE                   3
#define CH_BM_HUMIDITY                      4
#define CH_ENTRANCE_MOTION_DETECTED_SECONDS 5
#define CH_DOOR_MAIN_OPENED_MINUTES         6
#define CH_DOOR_TO_BASEMENT_OPENED_MINUTES  7
#define CH_DOOR_BASEMENT_OPENED_MINUTES     8
#define CH_DOOR_BACK_OPENED_MINUTES         9

#define CH_LR_RUNTIME                       21   // living room node
#define CH_LR_TEMPERATURE                   22
#define CH_LR_HUMIDITY                      23

#define CH_PS_RUNTIME                       41   // power station
#define CH_PS_TEMPERATURE                   42
#define CH_PS_HUMIDITY                      43
#define CH_PS_BATT_VOLTATE                  44

// digital states
#define CH_DOOR_MAIN                51
#define CH_DOOR_TO_BASEMENT         52
#define CH_DOOR_BASEMENT            53
#define CH_DOOR_BACK                54
#define CH_ENTRANCE_MOTION          55
#define CH_LIGHT_BASEMENT           56
#define CH_LIGHT_STAIR_BASEMENT     57
#define CH_ENTRANCE_LIGHT           58
#define CH_POWER_RADIO              59
#define CH_WATER_SMOKE_BASEMENT     60
#define CH_WATER_LEAK_1             61

#define CH_FORCE_RADIO_POWER        100


void cayenneSetup(){
  Serial.println("Cayenne connecting...");
  Cayenne.begin(dvUsername, dvPassword, dvClientID, wifiSsid, wifiPassword);
  Serial.println("Cayenne connected!");
  delay(200);
}

CAYENNE_OUT_DEFAULT(){
    Cayenne.virtualWrite(CH_PS_BATT_VOLTATE, ssBatteryVolt, "batt", "V");
    Cayenne.virtualWrite(CH_PS_RUNTIME, runtimeMinutes, "counter");
    Cayenne.celsiusWrite(CH_PS_TEMPERATURE, temp);
    Cayenne.virtualWrite(CH_PS_HUMIDITY, humidity, "rel_hum", "p");
    Cayenne.virtualWrite(CH_PS_HUMIDITY, humidity, "rel_hum", "p");

  // digital signals

}

void writeCayenneDigitalStates(int channelId, int value){
  delay(MESSAGE_DELAY);
  Cayenne.virtualWrite(channelId, value, "digital_sensor", "d");
}


#endif
