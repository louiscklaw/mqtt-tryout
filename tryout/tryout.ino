
// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);
    setup_FS();


}

// the loop function runs over and over again forever
void loop() {
    update_timeclient();

    Serial.println(get_time());

    delay(1000);
}
