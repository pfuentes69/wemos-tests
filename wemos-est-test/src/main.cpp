/**
   BasicHTTPSClient.ino

    Created on: 20.08.2018

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClientSecureBearSSL.h>
// Fingerprint for demo URL, expires on June 2, 2021, needs to be updated well before this date
const uint8_t fingerprint[20] = { 0x40, 0xaf, 0x00, 0x6b, 0xec, 0x90, 0x22, 0x41, 0x8e, 0xa3, 0xad, 0xfa, 0x1a, 0xe8, 0x25, 0x41, 0x1d, 0x1a, 0x54, 0xb3 };


const char *ssid = "Papillon";
const char *password = "70445312";


static const char CSR[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE REQUEST-----
MIHNMHYCAQAwFDESMBAGA1UEAwwJZGV2aWNlWHl6MFkwEwYHKoZIzj0CAQYIKoZI
zj0DAQcDQgAEb+gl/3/4JsBT/AkNeQag4SzaTCAOWwAE1NYQu6NIa5JA2eBadSeI
5GSwa8XGTRtn/RS4dLp9A6s6Tugtf+8sK6AAMAoGCCqGSM49BAMCA0cAMEQCICkM
PFFQm3yox9vjNwTXmfZNqsVt8KLS/861uAKub1prAiAT418WdAYB7mdgRwOMf7OT
Pbp9Km9+8DM7D0cQh5Zs4w==
-----END CERTIFICATE REQUEST-----
)EOF";

ESP8266WiFiMulti WiFiMulti;

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();
/*
  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }
*/
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);
}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

    //client->setFingerprint(fingerprint);
    // Or, if you happy to ignore the SSL certificate, then use the following line instead:
    client->setInsecure();

    HTTPClient https;

    Serial.print("[HTTPS] begin...\n");
//    http.begin("https://wksa-est.certifyiddemo.com:443/.well-known/est/simpleenroll");
//    http.begin(client, "https://wksa-est.certifyiddemo.com/.well-known/est/cacerts/");
//    http.begin(client, "https://httpbin.org/get");  
//    httpClient.setAuthorization("90af2231057f4505a92185e134d3fbe4", "d847f238c8e1453cadc1ddf0f6ba491d");
//    int statusCode = httpClient.POST((uint8_t*)CSR, 357);

//    if (https.begin(*client, "https://wksa-est.certifyiddemo.com/.well-known/est/cacerts/")) {  // HTTPS
    if (https.begin(*client, "https://httpbin.org/get")) {  // HTTPS

      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      int httpCode = https.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }

  Serial.println("Wait 10s before next round...");
  delay(10000);
}