#include <ESP8266WiFi.h>

const char* ssid = "logic_test";
const char* password = "1233211234567";

void setup_wifi()
{
    Serial.println("setting up wifi");

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 200 );
    Serial.print ( "." );
  }
}
