#include <ESP8266WiFi.h>
#include "global_vars.h"
#include "pin_define.h"
#include "sensors.h"
#include "blynk.h"
#include "cayenne.h"

#define ENABLE_WIFI
#define ENABLE_BLYNK
#define ENABLE_CAYENNE

// =======================================================
void setup() {
  ESP.wdtDisable();
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_AC_POWER_LIGHT, OUTPUT);

  Serial.begin(19200);
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
}

unsigned long previousMillis = millis();
unsigned long currentMillis = millis();
// =======================================================
void loop (){
  ESP.wdtFeed();

  currentMillis = millis();
  runtimeMinutes = currentMillis / 60000;
  if(abs(currentMillis - previousMillis) > 2000){  // sampling sensors every 2 sec
    previousMillis = currentMillis;             // save the last time  

#ifdef ENABLE_WIFI
  if(WiFi.status() == WL_DISCONNECTED){
    Serial.println("WiFi connection lost! Reconnecting...");
    WiFi.disconnect();
    WIFI_Connect();    
  }

    getServerTime();
#endif

    updateBattVolt();
    updateTempHumid();
    updateActuators();
  }
  
#ifdef ENABLE_WIFI
#ifdef ENABLE_CAYENNE
  Cayenne.loop();
#endif
#ifdef ENABLE_BLYNK
  blynkLoop();
#endif
#endif

  flipLed();
  delay(100);
}
