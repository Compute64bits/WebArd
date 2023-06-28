#include <SoftwareSerial.h>
#define serialCommunicationSpeed 115200

#define DEBUG false
SoftwareSerial esp8266(2, 3); // RX and TX

String UUID = "Livebox-XXXX";
String PASSWORD = "1234";

void setup(){
  Serial.begin(serialCommunicationSpeed);           
  esp8266.begin(serialCommunicationSpeed);     
  Serial.println("[*] Starting..."); 
  InitWifiModule();
  Serial.println("[*] ESP8266 is ready!");
}

void loop(){
  if(esp8266.available()){    
    if(esp8266.find("+IPD,")){
     int connectionId = esp8266.read()-48;

     // Create Webpage
     String webpage = "<body style=\"background: #0d1117; display: flex; justify-content: center;\"><a href=\"https://github.com/Compute64bits/WebArd/\" style=\"font-size: 64px; color: aliceblue; text-decoration: none; margin-top: calc(25% - 64px);\">WebArd";

     // Send webpage
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";

     sendData(cipSend,750,DEBUG);
     sendData(webpage,750,DEBUG);

     // Close client connection
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId;
     closeCommand+="\r\n";
     sendData(closeCommand,1000,DEBUG);
    }
  }
}

void sendData(String command, const int timeout, boolean debug){
    esp8266.print(command);
    long int time = millis();  
    while (millis() - time < timeout){
      if (esp8266.available()){
        char c = esp8266.read();
        if (debug){
          Serial.write(c);
          };
        }
    }
}

void InitWifiModule(){
  sendData("AT+RST\r\n", 2000, DEBUG);
  delay (2000);
  String connect_cmd = "AT+CWJAP=\"";
  connect_cmd += UUID;
  connect_cmd += "\", \"";
  connect_cmd += PASSWORD;
  connect_cmd += "\"\r\n";
  sendData(connect_cmd , 2000, DEBUG); // "AT+CWJAP=\"UUID\",\"PASSWORD\"\r\n"
  delay (5000);
  sendData("AT+CWMODE=1\r\n", 1500, DEBUG);
  delay (1500);
  sendData("AT+CIPMUX=1\r\n", 1500, DEBUG);
  delay (1500);
  sendData("AT+CIPSERVER=1,80\r\n", 1500, DEBUG);
}
