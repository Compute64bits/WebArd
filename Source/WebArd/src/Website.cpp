
#include "../ESP8266.hpp"


void serveWebsite(int connection,String page){

    String command = "AT+CIPSEND=";
    command += connection;
    command += ",";
    command += page.length();
    command += "\r\n";

    sendData(command,750);
    sendData(page,750);
}
