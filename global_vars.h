#ifndef GLOBAL_VARS
#define GLOBAL_VARS

long globalState = 0;
int debugCounter = 0;
int heartbeat = 0;

bool stateLed = 0;

// sensors
float temp = 0.0;
float humidity = 0.0;

float ssBatteryVolt = 0;

// actuators
bool acBuzzer = 0;

int playMelodyCounter = 0;
int runtimeMinutes = 0;

#endif
