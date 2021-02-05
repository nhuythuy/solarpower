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
#include <ArduinoJson.h>


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

  setupSensors();

  Serial.begin(19200);
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

// https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
// Potentiometer is connected to GPIO 34 (Analog ADC1_CH6) 
void loop (){
  runtimeMinutes = millis() / 60000;
  updateBattVolt();
  updateTempHumid();

  WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {
      stateLed = !stateLed;
      digitalWrite(PIN_LED, stateLed);
      Serial.println(".");
      String request = client.readStringUntil('\n');        // receives the message from the client
      Serial.print("Request from client: "); Serial.println(request);
      client.flush();

      DynamicJsonDocument doc(100);
      doc["node"] = "powerstation";
      doc["heartbeat"] = heartbeat++;
      doc["runtime"] = runtimeMinutes;
      doc["battvolt"] = ssBatteryVolt;
      doc["temp"] = String(temp, 2);
      doc["humidity"] = String(humidity, 2);

      char jsonSolarPower[100];
      serializeJson(doc, jsonSolarPower);
      client.println(String(jsonSolarPower) + "\n");
      Serial.println("Reply from server: " + String(jsonSolarPower));

      stateLed = !stateLed;
      digitalWrite(PIN_LED, stateLed);
    }
    client.stop();                // terminates the connection with the client
  }

  if(WiFi.status() == WL_DISCONNECTED){
    Serial.println("WiFi connection lost! Reconnecting...");
    WiFi.disconnect();
    WIFI_Connect();
  }

  delay(1000);
}
