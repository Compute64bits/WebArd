
#include "../ESP8266.hpp"


int sessionId(){
    return esp8266.read() - 48;
}


void closeSession(int connection){

    String command = "AT+CIPCLOSE=";
    command += connection;
    command += "\r\n";

    sendData(command,1000);
}
