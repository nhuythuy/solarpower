#ifndef ACTUATORS
#define ACTUATORS

void updateActuators(){
  if(ssBatteryVolt > 12.50) && ((currentHour > 20) || (currentHour < 7))){
    digitalWrite(PIN_AC_POWER_LIGHT, TRUE);
  }
  else{
    digitalWrite(PIN_AC_POWER_LIGHT, FALSE);
  }

}

#endif
