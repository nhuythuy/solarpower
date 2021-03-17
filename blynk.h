#include <BlynkSimpleEsp8266.h>
#include "wifi_cloud.h"
#include "global_vars.h"

int blynkCounter = 0;

#ifndef BLYNK
#define BLYNK

#define MESSAGE_DELAY                       100

#define VP_BATT_VOLTAGE                     V1
#define VP_PS_RUNTIME                       V2    // power station node
#define VP_PS_TEMPERATURE                   V3
#define VP_PS_HUMIDITY                      V4

#define VP_SYSTEM_TIME                      V10

#define VP_PS_AC_MAIN_DOOR_LIGHT_ON         V44   // status

// control signals, only available on Blynk
#define VP_PS_AC_MAIN_DOOR_LIGHT            V45
#define VP_PS_AC_LED_HEART_MODE             V46

// digital states
#define VP_AUTO_LOAD_POWER                V51
#define VP_MANUAL_LOAD_POWER_ON           V52

#define VP_FORCE_RADIO_POWER        V100
#define VP_FORCE_CAMERA_POWER       V101

#define BLYNK_PRINT Serial

#ifndef WIFI_INFO
#define WIFI_INFO
char ssid[] = WIFI_AP;
char pass[] = WIFI_PW;
#endif

char auth[] = BLYNK_PW;

BlynkTimer timer;

void blynkReconnect() {
  if (!Blynk.connected()) {
    if (Blynk.connect()) {
      BLYNK_LOG("Reconnected");
    }
    else {
      BLYNK_LOG("Not reconnected");
    }
  }
}


BLYNK_WRITE(VP_AUTO_LOAD_POWER){
  autoLoadPower = (boolean)param.asInt();
  storeState(ADDRESS_AUTO_LOAD_POWER, autoLoadPower);
}

BLYNK_WRITE(VP_MANUAL_LOAD_POWER_ON){
  manualLoadPowerOn = (boolean)param.asInt();
  storeState(ADDRESS_MANUAL_LOAD_POWER_ON, manualLoadPowerOn);
}

BLYNK_WRITE(VP_PS_AC_LED_HEART_MODE){
  heartLedMode = param.asInt();
}

BLYNK_WRITE(VP_PS_AC_MAIN_DOOR_LIGHT){
  mainDoorLightMode = param.asInt();
}


// for all signals requested by Blynk app (slow response)
BLYNK_READ(VP_BATT_VOLTAGE){
  Blynk.virtualWrite(VP_BATT_VOLTAGE, ssBatteryVolt);
}

BLYNK_READ(VP_PS_RUNTIME){
  Blynk.virtualWrite(VP_PS_RUNTIME, runtimeMinutes);
}

BLYNK_READ(VP_PS_TEMPERATURE){
    Blynk.virtualWrite(VP_PS_TEMPERATURE, temp);
}

BLYNK_READ(VP_PS_HUMIDITY){
  Blynk.virtualWrite(VP_PS_HUMIDITY, humidity);
}

BLYNK_READ(VP_SYSTEM_TIME){
  Blynk.virtualWrite(VP_SYSTEM_TIME, systemHourMinute);
}


// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void blynkTimerEvent()
{
  yield();
  blynkReconnect();
  
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(VP_PS_AC_MAIN_DOOR_LIGHT_ON, (mainDoorLightOn ? 255 : 0));

  Serial.println("Blynk timer triggered...");
  // for all signals to be sent at once
}

void blynkSetup(){
  Serial.println("Connecting to Blynk ...");
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(500L, blynkTimerEvent);
  Serial.println("Connected to Blynk !");
  delay(200);
}

void blynkLoop(){
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}

#endif
