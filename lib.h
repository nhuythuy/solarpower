#include "global_vars.h"
#include "pin_define.h"
#include <EEPROM.h>


#ifndef LIB
#define LIB

#define ADDRESS_AUTO_LOAD_POWER     0
#define ADDRESS_MANUAL_LOAD_POWER_ON  1

void flipLed(){
  stateLed = !stateLed;
  digitalWrite(PIN_LED, stateLed);
}

void initMemory(){
  EEPROM.begin(128);  
}

int readState(int addr){
  int value = EEPROM.read(addr);
  Serial.println("Old values read at: " + String(addr) + ", " + String(value));
  return value;
}

void storeState(int addr, int value){
  EEPROM.put(addr, value);
  Serial.println("Write new values at: " + String(addr) + ", " + String(value));
  EEPROM.commit();
}


#endif
