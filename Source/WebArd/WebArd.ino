
#include "Config.hpp"
#include "ESP8266.hpp"
#include <Arduino.h>


/*
 *  RX : 2
 *  TX : 3
 */

SoftwareSerial esp8266(2,3);


void setup(){

    Serial.begin(serialSpeed);
    esp8266.begin(serialSpeed);

    Serial.println("[*] Starting...");

    initializeWiFi();

    Serial.println("[*] ESP8266 is ready!");
}


void loop(){

    if(!esp8266.available())
        return;

    if(!esp8266.find("+IPD,"))
        return;


    const int connection = sessionId();

    serveWebsite(connection,webpage);
    closeSession(connection);
}
