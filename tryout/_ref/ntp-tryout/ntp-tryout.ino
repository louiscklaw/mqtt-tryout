#include "NTPClient.h"
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

const char *ssid     = "logic_test";
const char *password = "1233211234567";

WiFiUDP ntpUDP;

// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset


// You can specify the time server pool and the offset, (in seconds)
// additionaly you can specify the update interval (in milliseconds).
// NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

NTPClient timeClient(ntpUDP, "stdtime.gov.hk", 3600*8, 60000);

void setup_wifi()
{
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 200 );
    Serial.print ( "." );
  }
}

void setup_NTP()
{
    setup_wifi();
    timeClient.begin();
}

String get_time()
{
    String strTemp = timeClient.getFormattedTime();
    return strTemp;
}

void setup(){
    Serial.begin(115200);

    setup_NTP();
}



void loop() {
  timeClient.update();

  Serial.println(get_time());

  delay(1000);
}
