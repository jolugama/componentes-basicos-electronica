/**
 * Detecta cuando el sonido es alto (configurable) 
 * útil para colocarlo al lado de un teléfono fijo, en el telefonillo de la puerta y dar señal de aviso.
 * Modificando el ejemplo se puede usar de ecualizador. 
*/
#include <Arduino.h>

const int sensorPIN = A0;
const int interval = 400;
const int minSoundDetect = 300;  // es el mínimo de sonido para detectar y avisar

unsigned long startMillis;
unsigned int signalMax;
unsigned int signalMin;

void setup() {
    Serial.begin(9600);
}

void loop() {
    startMillis = millis();
    signalMax = 0;
    signalMin = 1024;

    // Recopilar durante la ventana
    unsigned int sample;
    while (millis() - startMillis < interval) {
        sample = analogRead(sensorPIN);
        if (sample < 1024) {
            if (sample > signalMax) {
                signalMax = sample;  // Actualizar máximo
            } else if (sample < signalMin) {
                signalMin = sample;  // Actualizar mínimo
            }
        }
    }
    unsigned int peakToPeak = signalMax - signalMin;  // Amplitud del sonido
    //  Serial.println(volts);
    if (peakToPeak > 200) {
        Serial.println("Sonido alto");
    }
}