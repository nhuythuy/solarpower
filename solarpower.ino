/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Starts WiFi server with fix IP and listens
 *  Receives and sends messages to the client
 *  Communicates clients as diff. nodes
 *  ESP32
 */

#include <ESP8266WiFi.h>
#include "global_vars.h"
#include "pin_define.h"
#include "sensors.h"
#include "wifi_pw.h"
#include "comm_main.h"


#define DELAY_LONG        5000            // 5,0 seconds
#define DELAY_SHORT       1000

int serverHomeCounter = 0;

char ssid[] = "VNNO";                     // SSID of your home WiFi
char password[] = WIFI_PW;                // password of your home WiFi
WiFiServer server(80);                    

IPAddress ip(192, 168, 1, 6);             // IP address of the server: Solar power station
IPAddress gateway(192,168,1,1);           // gateway of your network
IPAddress subnet(255,255,255,0);          // subnet mask of your network

long delayMs = DELAY_SHORT;

void WIFI_Connect(){
  Serial.println();
  Serial.println("MAC: " + WiFi.macAddress());
  Serial.println("Connecting to " + String(ssid));

  WiFi.config(ip, gateway, subnet);       // forces to use the fix IP
  WiFi.begin(ssid, password);

  bool ledStatus = false;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

    ledStatus = !ledStatus;
    digitalWrite(PIN_LED, !ledStatus);
    if(debugCounter++ > 80)
    {
      debugCounter = 0;
      Serial.println("!");
    }
  }

  delay(500);
  Serial.println("\nConnected to wifi");
  Serial.print("Status: ");   Serial.println(WiFi.status());    // Network parameters
  Serial.print("IP: ");       Serial.println(WiFi.localIP());
  Serial.print("Subnet: ");   Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");  Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: ");     Serial.println(WiFi.SSID());
  Serial.print("Signal: ");   Serial.println(WiFi.RSSI());
  Serial.println();

  server.begin(); // starts the server
  delay(500);
}

void setup() {
  pinMode(PIN_LED, OUTPUT);

  Serial.begin(19200);

  setupSensors();
  WIFI_Connect();
}


void blinkLed(){
  stateLed = !stateLed;
  digitalWrite(PIN_LED, stateLed);
  delay(1000);
}

void delayWithErrorCheck(){
    if(globalState > 0)
    blinkLed();
  else
    delay(delayMs);
}


void loop (){
  runtimeMinutes = millis() / 60000;
  updateBattVolt();
  updateTempHumid();

  CommMain();

  if(WiFi.status() == WL_DISCONNECTED){
    Serial.println("WiFi connection lost! Reconnecting...");
    WiFi.disconnect();
    WIFI_Connect();
  }

  delay(1000);
}
