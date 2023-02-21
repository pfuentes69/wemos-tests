#include <Arduino.h>

/*
 *  This sketch trys to Connect to the best AP based on a given list
 *
 */

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;

void setup() {
  Serial.begin(115200);
  delay(10);

  wifiMulti.addAP("Papillon", "70445312");
  wifiMulti.addAP("Papillon_EXT", "70445312");
  wifiMulti.addAP("InsecureWifi", "");

	Serial.println("Connecting Wifi...");
  while(wifiMulti.run() != WL_CONNECTED) {
      Serial.print(".");
      delay(1000);
  }
  Serial.println();
  if(wifiMulti.run() != WL_CONNECTED) {
    Serial.println("WiFi not connected!");
    delay(1000);
  } else {
      Serial.println("WiFi connected");
      Serial.print("AP : ");
      Serial.println(WiFi.SSID());
      Serial.print("IP address : ");
      Serial.println(WiFi.localIP());
  }
}

void loop() {
}