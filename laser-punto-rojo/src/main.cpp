/**
 * Atención, las que tengo, están mal señaladas. La S es el GNS, y el - es el pinSensor. Son de 5v.
 * (láser 6mm 5V 5mW)
*/
#include <Arduino.h>

const int sensorPIN = 3;
// const int minSoundDetect = 300;  // es el mínimo de sonido para detectar y avisar

void setup() {
    Serial.begin(9600);
    pinMode(sensorPIN, OUTPUT);
}

void loop() {
    digitalWrite(sensorPIN, HIGH);
    Serial.println("Encendido");
    delay(4000);
    digitalWrite(sensorPIN, LOW);
     delay(4000);
    Serial.println("Apagado");
}