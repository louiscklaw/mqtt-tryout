
unsigned long previousMillis = 0;
const long interval = 1000;

const int ledPin = LED_BUILTIN;

void setup_LED(){
    Serial.println("setup led");
    pinMode(ledPin, OUTPUT);
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

    Serial.println(get_time());
  }
  return ledState;
}
