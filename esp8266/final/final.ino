#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"
#include <PubSubClient.h>

#define DHTTYPE DHT22

const char* ssid = "logic_test";
const char* password = "1233211234567";
const char* mqtt_server = "iot.eclipse.org";

ESP8266WebServer server(80);

uint8_t DHTPin = D1;

DHT dht(DHTPin, DHTTYPE);

float Temperature;
float Humidity;

int ledState = LOW;
const long interval = 1000;
unsigned long previousMillis = 0;
const int ledPin =  LED_BUILTIN;

WiFiClient espClient;
PubSubClient pubsub_client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;


void setup_LED(){
    Serial.println("setup led");
    pinMode(LED_BUILTIN, OUTPUT);
}

int blink_LED(int ledState){
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
  return ledState;
}


void setup_DHT(){
    Serial.println("setup dht");
    pinMode(DHTPin, INPUT);
    dht.begin();
}

void setup_WIFI(){
  Serial.println("setup wifi");
  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

}

void setup_HTTPServer(){
    Serial.println("setup http server");
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");

}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

void handle_OnConnect() {

  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity
  server.send(200, "text/html", SendHTML(Temperature, Humidity));
}

void setup_MQTT(){
    Serial.println("setup MQTT");
  pubsub_client.setServer(mqtt_server, 1883);
  pubsub_client.setCallback(callback);
}

void publish_Temp(float temp, float humid){

  if (!pubsub_client.connected()) {
    reconnect();
  }

  long now = millis();
  if (now - lastMsg > 10000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 50, "temp#%lf, humid#%lf", temp, humid);
    Serial.print("Publish message: ");
    Serial.println(msg);
    pubsub_client.publish("logictest/DO", msg);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
}

String SendHTML(float Temperaturestat, float Humiditystat) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"><meta http-equiv=\"refresh\" content=\"10\">\n";
  ptr += "<title>ESP8266 Weather Report</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr += "p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>ESP8266 NodeMCU Weather Report</h1>\n";

  ptr += "<p>Temperature: ";
  ptr += (int)Temperaturestat;
  ptr += "°C</p>";
  ptr += "<p>Humidity: ";
  ptr += (int)Humiditystat;
  ptr += "%</p>";

  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

void reconnect() {
  // Loop until we're reconnected
  while (!pubsub_client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (pubsub_client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      pubsub_client.publish("outTopic", "hello world");
      // ... and resubscribe
      pubsub_client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(pubsub_client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  delay(100);

  setup_LED();
  setup_WIFI();
  setup_DHT();
  setup_HTTPServer();

  setup_MQTT();
}


void loop() {
    float temp = dht.readTemperature();
    float humid = dht.readHumidity();
    publish_Temp(temp,humid);

    ledState = blink_LED(ledState);

    // handle http task
    server.handleClient();

    // handle mqtt task
    pubsub_client.loop();

}
