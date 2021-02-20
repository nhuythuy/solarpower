#include "global_vars.h"

#ifndef ACTUATORS
#define ACTUATORS

void updateActuators(){
  if((ssBatteryVolt > 12.50) && ((currentHour > 20) || (currentHour < 7))){
    digitalWrite(PIN_AC_LIGHT_MAIN_DOOR, HIGH);
  }
  else{
    digitalWrite(PIN_AC_LIGHT_MAIN_DOOR, LOW);
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
