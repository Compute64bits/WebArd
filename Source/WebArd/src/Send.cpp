
#include "../ESP8266.hpp"
#include "../Config.hpp"
#include <Arduino.h>


#ifdef DEBUG


void sendData(String command,const int timeout){

    esp8266.print(command);

    const auto time = millis();

    while(millis() - time < timeout){

        if(!esp8266.available())
            continue;

        char c = esp8266.read();

        Serial.write(c);
    }
}


#else


void sendData(String command,const int timeout){
    esp8266.print(command);
}


#endif
