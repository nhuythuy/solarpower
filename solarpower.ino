/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Starts WiFi server with fix IP and listens
 *  Receives and sends messages to the client
 *  Communicates clients as diff. nodes
 *  ESP32
 */

#include <ESP8266WiFi.h>
#include "global_vars.h"
#include "pin_define.h"
#include "sensors.h"
#include "comm_main.h"


#define WDT_TIMEOUT   300 // 300 sec

// =======================================================
void setup() {
  ESP.wdtDisable();
  pinMode(PIN_LED, OUTPUT);

  Serial.begin(19200);
  WIFI_Connect();

  setupSensors();

  ESP.wdtEnable(5000); // msec
}

// =======================================================
void loop (){
  ESP.wdtFeed();

  long mill = millis();
  runtimeMinutes = millis() / 60000;
  if((mill - ssSamplingTimer) > 2000){ // sampling sensors every 1 sec
    updateBattVolt();
    updateTempHumid();

    ssSamplingTimer = mill;
  }
  
  CommMain();

  if(WiFi.status() == WL_DISCONNECTED){
    Serial.println("WiFi connection lost! Reconnecting...");
    WiFi.disconnect();
    WIFI_Connect();
  }

  flipLed();
  delay(100);
}
