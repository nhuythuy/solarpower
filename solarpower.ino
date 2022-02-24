#include <ESP8266WiFi.h>
#include "global_vars.h"
#include "pin_define.h"
#include "sensors.h"
#include "blynk.h"
#include "cayenne.h"
#include "actuators.h"

#define ENABLE_WIFI
#define ENABLE_BLYNK
#define ENABLE_CAYENNE

// =======================================================
void setup() {
  ESP.wdtDisable();
  setupActuators();

  Serial.begin(115200);
#ifdef ENABLE_WIFI
  WIFI_Connect();
  setupDateTime();

#ifdef ENABLE_CAYENNE
  cayenneSetup();
#endif
#ifdef ENABLE_BLYNK
  blynkSetup();
#endif
#endif

  setupSensors();

  ESP.wdtEnable(5000); // msec

  autoLoadPower = (boolean)readState(ADDRESS_AUTO_LOAD_POWER);
  manualLoadPowerOn = (boolean)readState(ADDRESS_MANUAL_LOAD_POWER_ON);
}

unsigned long previousMillis = millis();
unsigned long currentMillis = millis();
// =======================================================
void loop (){
  ESP.wdtFeed();

  yield();
  currentMillis = millis();
  runtimeMinutes = currentMillis / 60000;
  long millDiff = currentMillis - previousMillis;
  if(abs(millDiff) > 2000){  // sampling sensors every 2 sec
    previousMillis = currentMillis;             // save the last time  

#ifdef ENABLE_WIFI
  if(WiFi.status() == WL_DISCONNECTED){
    Serial.println("WiFi connection lost! Reconnecting...");
    WiFi.disconnect();
    WIFI_Connect();    
  }

    yield();
    getServerTime();
#endif

    yield();
    updateBattVolt();
    yield();
    updateTempHumid();
    yield();
    updateActuators();
  }
  
#ifdef ENABLE_WIFI
#ifdef ENABLE_CAYENNE
  yield();
  Cayenne.loop();
#endif
#ifdef ENABLE_BLYNK
  yield();
  blynkLoop();
#endif
#endif

  flipLed();
  delay(100);
}
