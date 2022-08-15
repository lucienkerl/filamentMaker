//
// Created by lucienkerl on 04.08.22.
//

#include "Network.h"
#include "config.h"
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

void Network::setup() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }
    ArduinoOTA.begin();
    Serial.println(WiFi.localIP());
}

void Network::loop() {
    ArduinoOTA.handle();
}
