#include "DHT.h"

#define DHTTYPE DHT22

uint8_t DHTPin = D1;

DHT dht(DHTPin, DHTTYPE);

void setup_DHT(){
    Serial.println("setup dht");
    pinMode(DHTPin, INPUT);
    dht.begin();
}

float read_temperature()
{
    float temp = dht.readTemperature();
    return temp;

}

float read_humidity()
{
    float humid = dht.readHumidity();
    return humid;
}
