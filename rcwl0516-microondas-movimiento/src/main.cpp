/**
 * Emite señales de microondas, tanto por delante (más fuerte) como por detrás. Atraviesa paredes, 
 * hasta 1m de distancia.
*/
#include <Arduino.h>

const int LEDPin = 13;
const int sensorPIN = 3;
const int interval = 400;
// const int minSoundDetect = 300;  // es el mínimo de sonido para detectar y avisar

void setup() {
    Serial.begin(9600);
    pinMode(LEDPin, OUTPUT);
    pinMode(sensorPIN, INPUT);
}

void loop() {
    unsigned long startMillis = millis();

    unsigned int value;
    while (millis() - startMillis < interval) {
        value = digitalRead(sensorPIN);
        if (value == HIGH) {
            digitalWrite(LEDPin, HIGH);
            delay(100);
            digitalWrite(LEDPin, LOW);
            delay(50);
        } else {
            digitalWrite(LEDPin, LOW);
        }
    }

    Serial.println(value);
}