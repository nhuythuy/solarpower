#include <ArduinoJson.h>
#include "lib.h"
#include "wifi_cloud.h"

void CommMain(){
  WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {
      flipLed();
      Serial.println(".");
      String request = client.readStringUntil('\n');    // receives the message from the client
      Serial.print("Request from client: "); Serial.println(request);
      client.flush();

      DynamicJsonDocument doc(100);
      doc["node"] = "powerstation";
      doc["heartbeat"] = heartbeat++;
      doc["runtime"] = runtimeMinutes;
      doc["battvolt"] = ssBatteryVolt;
      doc["temp"] = String(temp, 2);
      doc["humidity"] = String(humidity, 2);
    
      char jsonHomeMain[100];
      serializeJson(doc, jsonHomeMain);
      client.println(String(jsonHomeMain) + "\n");
      Serial.println("Reply from server: " + String(jsonHomeMain));

      flipLed();
    }
    client.stop();                // tarminates the connection with the client
  }

}
