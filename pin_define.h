// https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/
// IMPORTANT NOTE: Remove PIN_SS_DOOR_MAIN connector b4 uploading code to NodeMcu, uploading fail otherwise

// inputs D1, D2, D5, D6, D7
#define PIN_SS_SUPPLY_VOLT          A0 // battery voltage

#define PIN_SS_I2C_SCL              D1
#define PIN_SS_I2C_SDA              D2

// outputs
#define PIN_LED                     D4 // same as built in LED GPIO22

#define PIN_AC_CAM_POWER            D5 // No. 1, power for entrance led
//#define PIN_AC_POWER_LIGHT          D3 // OK as output
#define PIN_AC_LIGHT_MAIN_DOOR      D6
#define PIN_AC_LED_HEART_LEFT       D7
#define PIN_AC_LED_HEART_RIGHT      D8

// remaining pins: RX (in), D3
