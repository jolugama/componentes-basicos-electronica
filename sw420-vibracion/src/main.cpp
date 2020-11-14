/**
 * Sensor vibración (3,3 V-5V)
*/
#include <Arduino.h>

const byte sensorPIN = 3;
const byte LedPin = 13;

void setup() {
    Serial.begin(9600);
    pinMode(sensorPIN, INPUT_PULLUP);
    pinMode(LedPin, OUTPUT);
    digitalWrite(LedPin, LOW);
}

void loop() {
    Serial.println(digitalRead(sensorPIN), DEC);
    delay(300);
    if (digitalRead(sensorPIN) == 1) {
        digitalWrite(LedPin, HIGH);
        // delay(3000);
    } else {
        digitalWrite(LedPin, LOW);
    }
}