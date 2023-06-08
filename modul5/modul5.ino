#include <WiFi.h>
#include "SinricPro.h"
#include "SinricProSwitch.h"

#define WIFI_SSID "Halal"
#define WIFI_PASS "indonesia"
#define APP_KEY "92c9511e-917d-4ac3-8145-10cd8be8b687"
#define APP_SECRET "7dacff1a-b8dd-44a9-83a8-7ac081d5efbc-9dfdc4f9-5f52-4c7d-bf38-6869b6e87528"
#define SWITCH_ID_1 "646e309f929949c1da70f74f"

#define RELAY_PIN 25
#define BAUD_RATE 9600

bool onPowerState1(const String &deviceId, bool &state){
    Serial.printf("Device 1 Turned", state?"on":"off");
    digitalWrite(RELAY_PIN, state);
    return true;
}

void setupWiFi() {
    Serial.printf("\r\n[WIFI]: Connecting");
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(250);  
    }
  // Serial.printf("connected \r\n[]wifi: IP Address is %s\r\n", WiFi.localIP().toString.c_str());
}

void setupSinricPro(){
  SinricProSwitch& mySwitch1 = SinricPro[SWITCH_ID_1];
  mySwitch1.onPowerState(onPowerState1);

  SinricPro.onConnected([](){
    Serial.printf("Connected to Sirik");
    });
  SinricPro.onDisconnected([](){
    Serial.printf("Disconnected from Sirik");
    });
  SinricPro.begin(APP_KEY, APP_SECRET);
}

void setup(){
  Serial.begin(BAUD_RATE);
  Serial.printf("\r\n\r\n");
  pinMode(RELAY_PIN, OUTPUT);
  setupWiFi();
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
}