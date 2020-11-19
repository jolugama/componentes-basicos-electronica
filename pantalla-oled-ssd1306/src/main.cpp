/**************************************************************************
128x64 - Pantalla OLED conectado con I2C
Ejemplo de lectura de cualquier sensor en el puerto 34 de un esp32
Se muestra en pantalla OLED, mediante la librería Adafruit. 

Con estas pantallas monocrómicas se puede hacer efectos de figuras, textos de diferentes tamaños, scroll
Para más información:
https://learn.adafruit.com/monochrome-oled-breakouts/arduino-library-and-examples

https://cdn-learn.adafruit.com/downloads/pdf/adafruit-gfx-graphics-library.pdf

 **************************************************************************/

#include <Adafruit_GFX.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

// pines usados
const byte sensorPin = 34;
const byte buttonPin = 36;

// constantes
const int ANALOG_MAX = 4096;  // en arduino es 1023. Depende de los bit elegidos en la funcion configAnalog, variable analogSetWidth
const float VOLT = 3.3;

const byte SCREEN_WIDTH = 128;  // ancho de la pantalla OLED
const byte SCREEN_HEIGHT = 64;  // alto de la pantalla OLED

// Declaración para una pantalla  SSD1306 conectado con I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 4);  //4 es el reset. no tocar.

// privadas
#include "button.h"
#include "effectExamples.h"
#include "images.h"
#include "osciloscope.h"

// privadas2
#include "smile.h"

// variables

void configAnalog() {
    analogSetWidth(12);                            // Sets the sample bits and read resolution, default is 12-bit (0 - 4095), range is 9 - 12 bits
                                                   //  9-bit gives an ADC range of 0-511
                                                   // 10-bit gives an ADC range of 0-1023
                                                   // 11-bit gives an ADC range of 0-2047
                                                   // 12-bit gives an ADC range of 0-4095                           // 10 bits son los que usa arduino.
    analogSetPinAttenuation(sensorPin, ADC_11db);  // 11 es el máximo, se acerca al de arduino.
    // Sets the input attenuation, default is ADC_11db, range is ADC_0db, ADC_2_5db, ADC_6db, ADC_11db
    // ADC_0db provides no attenuation so IN/OUT = 1 / 1 an input of 3 volts remains at 3 volts before ADC measurement
    // ADC_2_5db provides an attenuation so that IN/OUT = 1 / 1.34 an input of 3 volts is reduced to 2.238 volts before ADC measurement
    // ADC_6db provides an attenuation so that IN/OUT = 1 / 2 an input of 3 volts is reduced to 1.500 volts before ADC measurement
    // ADC_11db provides an attenuation so that IN/OUT = 1 / 3.6 an input of 3 volts is reduced to 0.833 volts before ADC measurement
    analogSetClockDiv(1);  // Set the divider for the ADC clock, default is 1, range is 1 - 255
}

void setup() {
    Serial.begin(115200);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Si falla, revisar con un escaneador de i2c
        Serial.println(F("No encuentra OLED SSD1306 en esa dirección I2C"));
        for (;;)
            ;  // infinito, hasta que detecte la pantalla.
    }

    display.display();

    delay(300);
    // testscrolltext();    // Draw scrolling text
    // testdrawbitmap();    // Draw a small bitmap image

    // display.invertDisplay(true);
    // delay(1000);
    // display.invertDisplay(false);
    // delay(1000);
    // testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT); // Animate bitmaps

    display.setRotation(0);  //orientacion del display 0,1,2,3
    display.setTextColor(WHITE);
    display.setTextSize(1);

    configAnalog();

    display.clearDisplay();

    display.display();

    display.setTextSize(1);

    smile::speak("Hola Jose");
    delay(1000);
    smile::speak("Como va todo?");
    delay(1000);
    smile::smile("Pasa un buen dia!");
    delay(4000);
    // display.setTextColor(WHITE);

    button::setup(buttonPin);
}

void loop() {
    display.clearDisplay();
    osciloscope::paintAxes();
    osciloscope::drawValues();
    display.display();
    button::loop(buttonPin);
}
