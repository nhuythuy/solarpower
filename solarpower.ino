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


#define DELAY_LONG        5000            // 5,0 seconds
#define DELAY_SHORT       1000

int serverHomeCounter = 0;


void setup() {
  pinMode(PIN_LED, OUTPUT);

  Serial.begin(19200);

  setupSensors();
  WIFI_Connect();
}


void blinkLed(){
  stateLed = !stateLed;
  digitalWrite(PIN_LED, stateLed);
  delay(1000);
}

void delayWithErrorCheck(){
    if(globalState > 0)
    blinkLed();
  else
    delay(delayMs);
}


void loop (){
  runtimeMinutes = millis() / 60000;
  updateBattVolt();
  updateTempHumid();

  CommMain();

  if(WiFi.status() == WL_DISCONNECTED){
    Serial.println("WiFi connection lost! Reconnecting...");
    WiFi.disconnect();
    WIFI_Connect();
  }

  delay(1000);
}
