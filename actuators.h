#include "global_vars.h"

#ifndef ACTUATORS
#define ACTUATORS

void setupActuators(){
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_AC_LED_HEART_LEFT, OUTPUT);
  pinMode(PIN_AC_LED_HEART_RIGHT, OUTPUT);
  pinMode(PIN_AC_LIGHT_MAIN_DOOR, OUTPUT);  
}

void updateActuators(){
  Serial.println("Batt Volt: " + String(ssBatteryVolt, 2) + ", Current house: " + String(currentHour));

  if(((currentHour > 19) || (currentHour < 8))){
    if(ssBatteryVolt > 12.3){ // 12.3
      Serial.println("Main door LIGHT ON!");
      mainDoorLightOn = 1;
      digitalWrite(PIN_AC_LIGHT_MAIN_DOOR, LOW);
    }
    if(ssBatteryVolt < 11.80){ // 11.8
      Serial.println("Main door LIGHT OFF!");
      mainDoorLightOn = 0;
      digitalWrite(PIN_AC_LIGHT_MAIN_DOOR, HIGH);
    }
  }
}

void updateLedHeart(){
  if(heartLedMode = 0){
    digitalWrite(PIN_AC_LED_HEART_LEFT, LOW);
    digitalWrite(PIN_AC_LED_HEART_RIGHT, LOW);
  }
  else if(heartLedMode == 255){
    digitalWrite(PIN_AC_LED_HEART_LEFT, HIGH);
    digitalWrite(PIN_AC_LED_HEART_RIGHT, HIGH);
  }
  else{}

}

void updateLightMainDoor(){
  if(mainDoorLightMode = 0)
    digitalWrite(PIN_AC_LIGHT_MAIN_DOOR, LOW);
  else if(mainDoorLightMode == 255)
    digitalWrite(PIN_AC_LIGHT_MAIN_DOOR, HIGH);
  else{}

}

#endif
