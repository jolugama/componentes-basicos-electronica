/**
 * Emite señales de microondas, tanto por delante (más fuerte) como por detrás. Atraviesa paredes, 
 * hasta 1m de distancia.
*/
#include <Arduino.h>

// son pines pwm de mega.
const byte rojoPin = 11;
const byte verdePin = 10;
const byte azulPin = 9;

void setup() {
    Serial.begin(9600);
    pinMode(rojoPin, OUTPUT);
    pinMode(verdePin, OUTPUT);
    pinMode(azulPin, OUTPUT);
}

void loop() {
    analogWrite(rojoPin, 0);
    analogWrite(verdePin, 255);
    analogWrite(azulPin, 255);
    delay(1000);
    analogWrite(rojoPin, 255);
    analogWrite(verdePin, 0);
    analogWrite(azulPin, 255);
    delay(1000);
    analogWrite(rojoPin, 100);
    analogWrite(verdePin, 255);
    analogWrite(azulPin, 0);
    delay(1000);
}