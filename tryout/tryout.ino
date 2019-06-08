

// the setup function runs once when you press reset or power the board
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);


    setup_DHT();

    setup_FS();


}

// the loop function runs over and over again forever
void loop() {
    update_timeclient();

    Serial.println(get_time());

    Serial.println(read_temperature());

    delay(1000);
}
