#!/usr/bin/env python3

import paho.mqtt.client as mqtt

TOPIC = "logictest/#"

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print('on connect')
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    print('call to subscribe')
    client.subscribe(TOPIC)


def on_subscribe(client, userdata, mid, granted_qos):
    print('on subscribe')

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

    if str(msg.payload) != b"test":
        print(str(userdata))

        for i in range(0,9):
            print('sending back')
            client.publish('logictest/DO','test')

def on_publish(client, userdata, mid):
    print('on publish')

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.on_subscribe = on_subscribe
client.on_publish = on_publish

client.connect("test.mosquitto.org", 1883, 60)
# publish.single("logictest/DO", "payload", hostname="test.mosquitto.org")


# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_forever()
