#include "global_vars.h"

#ifndef ACTUATORS
#define ACTUATORS

void updateActuators(){
  if((ssBatteryVolt > 12.50) && ((currentHour > 20) || (currentHour < 7))){
    digitalWrite(PIN_AC_POWER_LIGHT, HIGH);
  }
  else{
    digitalWrite(PIN_AC_POWER_LIGHT, LOW);
  }

}

#endif
