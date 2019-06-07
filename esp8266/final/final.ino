#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

#define DHTTYPE DHT22

const char* ssid = "logic_test";
const char* password = "1233211234567";

ESP8266WebServer server(80);

uint8_t DHTPin = D1;

DHT dht(DHTPin, DHTTYPE);

float Temperature;
float Humidity;

void setup_LED(){
    pinMode(LED_BUILTIN, OUTPUT);
}

int blink_LED(int current_state){
    int next_state=0;
    if (current_state == 1){
        digitalWrite(LED_BUILTIN, HIGH);
    }else{
        digitalWrite(LED_BUILTIN, LOW);
        next_state = 1;
    }
    return next_state;
}

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  setup_LED();

}

int led_state = 0;
void loop() {

    delay(1000);
    led_state = blink_LED(led_state);
}
