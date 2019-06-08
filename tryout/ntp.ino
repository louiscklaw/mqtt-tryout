#include "NTPClient.h"
#include <WiFiUdp.h>

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "stdtime.gov.hk", 3600*8, 60000);


void update_timeclient()
{
    timeClient.update();
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
