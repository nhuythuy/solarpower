// https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/
// IMPORTANT NOTE: Remove PIN_SS_DOOR_MAIN connector b4 uploading code to NodeMcu, uploading fail otherwise

// inputs D1, D2, D5, D6, D7
#define PIN_SS_SUPPLY_VOLT          A0 // battery voltage

#define PIN_SS_I2C_SCL              D1
#define PIN_SS_I2C_SDA              D2

// outputs
#define PIN_LED                     D4 // same as built in LED GPIO22
#define PIN_TONE_MELODY             D8

// remaining pins: RX (in), D3
