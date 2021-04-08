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

void turnOnEntranceLight(){
  Serial.println("Auto: Main door LIGHT ON!");
  mainDoorLightOn = 1;
  digitalWrite(PIN_AC_LIGHT_MAIN_DOOR, LOW);  
}

void turnOffEntranceLight(){
  Serial.println("Auto: Main door LIGHT OFF!");
  mainDoorLightOn = 0;
  digitalWrite(PIN_AC_LIGHT_MAIN_DOOR, HIGH);
}

void updateEntranceLight(){
  if(ssBatteryVolt > 13.3){
    if((currentMonth > 3) && (currentMonth < 11)){ // from April to October
      if((currentHour > 18) || (currentHour < 8)){
        updateEntranceLight();
      }
      else{
        turnOffEntranceLight();
      }
    }
    else // from November to March
    {
      if((currentHour > 17) || (currentHour < 7)){
        updateEntranceLight();
      }
      else{
        turnOffEntranceLight();
      }      
    }
  }
  else if(ssBatteryVolt < 13.0){
    turnOffEntranceLight();
  }    
}

void updateActuators(){
  Serial.println("Batt Volt: " + String(ssBatteryVolt, 2) + ", Current hour: " + String(currentHour));

  if(autoLoadPower){
  }
  else{ // autoLoadPower == OFF or MANUAL activated
    if(manualLoadPowerOn && (ssBatteryVolt > 13.3)){
      turnOnEntranceLight();
    }
    else{
      turnOffEntranceLight();
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
