#ifndef GLOBAL_VARS
#define GLOBAL_VARS

#define DELAY_LONG        5000      // 5,0 seconds
#define DELAY_SHORT       2500
long delayMs = DELAY_SHORT;

long globalState = 0;
int debugCounter = 0;

bool enableLoadPowerRead = false;
bool enableLoadPower = false;

bool stateLed = 0;

// sensors
float temp = 0.0;
float humidity = 0.0;

float ssBatteryVolt = 0;

// actuators
bool acBuzzer = 0;

int playMelodyCounter = 0;
int runtimeMinutes = 0;

bool mainDoorLightOn = 0;

int mainDoorLightMode = 0;
int heartLedMode = 0;

#endif
