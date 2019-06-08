
int ledState = LOW;


// the setup function runs once when you press reset or power the board
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);

    setup_wifi();

    setup_mqtt();

    setup_DHT();

    setup_FS();

    setup_LED();
}

// the loop function runs over and over again forever
void loop() {
    update_timeclient();

    float temp = read_temperature();
    float humid = read_humidity();

    publish_Temp(temp,humid);
    handle_mqtt();

    ledState = blink_LED(ledState);
}
