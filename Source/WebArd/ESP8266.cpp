
#include "ESP8266.hpp"
#include "Config.hpp"


int sessionId(){
    return esp8266.read() - 48;
}


void sendData(String command,const int timeout){

    esp8266.print(command);

    #ifdef DEBUG

        const auto time = millis();

        while(millis() - time < timeout){

            if(!esp8266.available())
                continue;

            char c = esp8266.read();

            Serial.write(c);
        }

    #endif
}


void closeClient(int connection){

    String command = "AT+CIPCLOSE=";
    command += connection;
    command += "\r\n";

    sendData(command,1000);
}


void initializeWifi(){

    sendData("AT+RST\r\n",2000);

    delay(2000);

    String command = "AT+CWJAP=\"";
    command += UUID;
    command += "\", \"";
    command += PASSWORD;
    command += "\"\r\n";

    sendData(command,2000);

    delay(5000);

    sendData("AT+CWMODE=1\r\n",1500);

    delay(1500);

    sendData("AT+CIPMUX=1\r\n",1500);

    delay(1500);

    sendData("AT+CIPSERVER=1,80\r\n",1500);
}


void serveWebsite(String page){

    String command = "AT+CIPSEND=";
    command += connectionId;
    command += ",";
    command += page.length();
    command += "\r\n";

    sendData(command,750,DEBUG);
    sendData(page,750,DEBUG);
}
