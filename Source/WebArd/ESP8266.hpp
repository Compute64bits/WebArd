#ifndef Header_ESP8266
#define Header_ESP8266


extern SoftwareSerial esp8266;


/**
 *  @brief Sends a close request to the client.
 */

void closeClient(int connection);


/**
 *  @brief Sends a command to the ESP8266.
 */

void sendData(String command,const int timeout);


/**
 *  @brief Setup wifi module settings.
 */

void initializeWiFi();


/**
 *  @brief Reads the connection id.
 */

int sessionId();


/**
 *  @brief Serves the given website over WiFi.
 */

void serveWebsite(String page);


#endif
