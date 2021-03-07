#include "global_vars.h"

#ifndef ACTUATORS
#define ACTUATORS

void setupActuators(){
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_AC_LED_HEART_LEFT, OUTPUT);
  pinMode(PIN_AC_LED_HEART_RIGHT, OUTPUT);
  pinMode(PIN_AC_LIGHT_MAIN_DOOR, OUTPUT);
  digitalWrite(PIN_AC_LIGHT_MAIN_DOOR, HIGH); // light OFF at startup
}

void updateActuators(){
  Serial.println("Batt Volt: " + String(ssBatteryVolt, 2) + ", Current house: " + String(currentHour));

  if(autoLoadPower){
    if((currentHour > 18) || (currentHour < 8)){
      if(ssBatteryVolt > 13.3){
        Serial.println("Auto: Main door LIGHT ON!");
        mainDoorLightOn = 1;
        digitalWrite(PIN_AC_LIGHT_MAIN_DOOR, LOW);
      }
      else if(ssBatteryVolt < 12.8){
        Serial.println("Auto: Main door LIGHT OFF!");
        mainDoorLightOn = 0;
        digitalWrite(PIN_AC_LIGHT_MAIN_DOOR, HIGH);
      }
    }
    else{  // turn light OFF
      Serial.println("Auto: Main door LIGHT OFF!");
      mainDoorLightOn = 0;
      digitalWrite(PIN_AC_LIGHT_MAIN_DOOR, HIGH);
    }
  }
  else{ // autoLoadPower == OFF or MANUAL activated
    if(manualLoadPowerOn){
      Serial.println("Manual: Main door LIGHT ON!");
      mainDoorLightOn = 1;
      digitalWrite(PIN_AC_LIGHT_MAIN_DOOR, LOW);
    }
    else if(ssBatteryVolt < 12.8){
      Serial.println("Manual: Main door LIGHT OFF!");
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
