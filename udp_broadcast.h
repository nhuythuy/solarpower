#include <WiFi.h>
#include "global_vars.h"
#include "auth_settings.h"
#include <WiFiUdp.h>
#include <ArduinoJson.h>

#ifndef UDP_BROADCAST
#define UDP_BROADCAST

WiFiUDP udp;

#define BROADCAST_IP    "192.168.1.255"
#define BROADCAST_PORT  45678

#define BUFFER_LENGTH   200

byte buffJson[BUFFER_LENGTH];
String sJson;

void setupUdp(){
  udp.begin(BROADCAST_PORT);
}

void receiveUdp(){
  int pkSize = udp.parsePacket();
  if(pkSize){
    char pktBuf[pkSize];
    Serial.print(udp.remoteIP());
    Serial.print(":");
    Serial.println(udp.remotePort());
    udp.read(pktBuf, pkSize);
    udp.stop();
    //udp.begin(BROADCAST_PORT);
    String sJson = String(pktBuf);
    Serial.println(sJson);
//    for (int i = 0; i < pktSize; i++) {
//      Serial.print(pktBuf[i], HEX);
//      Serial.print("\t");
//    }
//    Serial.println();
  }
  
}

#endif
