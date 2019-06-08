#include <ESP8266WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient pubsub_client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;

const char* mqtt_server = "iot.eclipse.org";

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
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

void setup_mqtt(){
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

void handle_mqtt()
{
    pubsub_client.loop();
}
