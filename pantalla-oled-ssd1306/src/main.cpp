/**************************************************************************
128x64 - Pantalla OLED conectado con I2C
Ejemplo de lectura de cualquier sensor en el puerto 34 de un esp32
Se muestra en pantalla OLED, mediante la librería Adafruit. 

Con estas pantallas monocrómicas se puede hacer efectos de figuras, textos de diferentes tamaños, scroll
 **************************************************************************/

#include <Adafruit_GFX.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

// constantes
const byte sensorPin = 34;
const int MAX_POSITION = 600; // en la mayoría de los sensores es 1023
const byte SCREEN_WIDTH = 128;  // ancho de la pantalla OLED
const byte SCREEN_HEIGHT = 64;  // alto de la pantalla OLED

// Declaración para una pantalla  SSD1306 conectado con I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 4);  //4 es el reset. no tocar.

// privadas
#include "effectExamples.h"

// variables
byte x = 0;
int getValueSensor = 0;

byte data[SCREEN_WIDTH];  // para guardar las lecturas
byte horizontalPosition = 0;
byte anterior;

void setup() {
    Serial.begin(115200);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Si falla, revisar con un escaneador de i2c
        Serial.println(F("No encuentra OLED SSD1306 en esa dirección I2C"));
        for (;;)
            ;  // infinito
    }

    display.display();

    // delay(2000);
    // testscrolltext();    // Draw scrolling text
    // testdrawbitmap();    // Draw a small bitmap image

    // display.invertDisplay(true);
    // delay(1000);
    // display.invertDisplay(false);
    // delay(1000);
    // testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT); // Animate bitmaps


}

void loop() {
    analogSetWidth(10);                           // 10 bits son los que usa arduino.
    analogSetPinAttenuation(sensorPin, ADC_11db);  // 11 es el máximo, se acerca al de arduino.
    display.clearDisplay();
    horizontalPosition = horizontalPosition % SCREEN_WIDTH;
    getValueSensor = analogRead(sensorPin);
    data[horizontalPosition] = SCREEN_HEIGHT * getValueSensor / MAX_POSITION;  // es por los 10 bit. modificar si se cambia.
    horizontalPosition++;
    byte i = horizontalPosition;
    Serial.println(analogRead(sensorPin));
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        i = i % SCREEN_WIDTH;
        display.drawLine(x, data[i] - 1, x, anterior, 1);
        anterior = data[i];
        i++;
        if (x == 0) {
            display.clearDisplay();
        }
    }
    display.display();
}
