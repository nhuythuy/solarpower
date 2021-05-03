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
  lastDebugCode = 0;
  if(ssBatteryVolt > 13.2){
    int eveningTimeToTurnOn = 17;                   // same for all days of a year
    int morningTimeToTurnOff = 7;                   // from November to March, shorter day with sunlight
    if((currentMonth >= 5) && (currentMonth <= 8)){ // from May to August, longest day with sunlight
      morningTimeToTurnOff = 2;
      eveningTimeToTurnOn = 22;
      lastDebugCode = 1;
    }
    else if(currentMonth == 4){  // April longer day with sunlight
      morningTimeToTurnOff = 5;
      eveningTimeToTurnOn = 20;
      if(currentDate > 15)        // one more hour delay last half days of month
        eveningTimeToTurnOn = 21;
      lastDebugCode = 2;
    }
    else if(currentMonth == 9){   // September, longer day with sunlight
      morningTimeToTurnOff = 5;
      eveningTimeToTurnOn = 20;
      if(currentDate < 15)        // one more hour delay first half days of this month
        eveningTimeToTurnOn = 21;
      lastDebugCode = 2;
    }
    else{                         // the rest of the year: short day with sunlight
      morningTimeToTurnOff = 7;
      eveningTimeToTurnOn = 17;
      lastDebugCode = 3;
    }
    
    if((currentHour >= eveningTimeToTurnOn) || (currentHour <= morningTimeToTurnOff)){
      turnOnEntranceLight();
      lastDebugCode = 10 + lastDebugCode;
    }
    else{
      turnOffEntranceLight();
      lastDebugCode = 20 + lastDebugCode;
    }      
  }
  else if(ssBatteryVolt < 13.0){
    turnOffEntranceLight();
    lastDebugCode = 30 + lastDebugCode;
  }    
  Serial.println("Last debug code: " + String(lastDebugCode));
}

void updateActuators(){
  Serial.println("Batt Volt: " + String(ssBatteryVolt, 2) + ", Current hour: " + String(currentHour));

  if(autoLoadPower){
    updateEntranceLight();
  }
  else{ // autoLoadPower == OFF or MANUAL activated
    if(manualLoadPowerOn && (ssBatteryVolt > 13.2)){
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
