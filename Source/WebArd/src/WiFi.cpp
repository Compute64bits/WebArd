
#include "../ESP8266.hpp"
#include "../Config.hpp"
#include <Arduino.h>


void initializeWiFi(){

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
