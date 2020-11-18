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

// constantes
const byte sensorPin = 34;
const int ANALOG_MAX = 4096;  // en arduino es 1023. Depende de los bit elegidos en la funcion configAnalog, variable analogSetWidth
const float VOLT = 3.3;

const byte SCREEN_WIDTH = 128;  // ancho de la pantalla OLED
const byte SCREEN_HEIGHT = 64;  // alto de la pantalla OLED

// Declaración para una pantalla  SSD1306 conectado con I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 4);  //4 es el reset. no tocar.

// privadas
#include "effectExamples.h"
#include "button.h"

// variables
byte x = 0;
int getValueSensor = 0;

byte dataArray[SCREEN_WIDTH];
byte horizontalPosition = 0;
byte horizontalPositionBefore;
float currentVolt;

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

    // delay(2000);
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

     button::setup(36);
}

void drawValues() {
    horizontalPosition = horizontalPosition % SCREEN_WIDTH;
    getValueSensor = analogRead(sensorPin);
    dataArray[horizontalPosition] = SCREEN_HEIGHT * getValueSensor / ANALOG_MAX;

    horizontalPosition++;
    byte i = horizontalPosition;
    // Serial.println(analogRead(sensorPin));
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        // Serial.println(i);
        // delay(1000);
        i = i % SCREEN_WIDTH;
        display.drawLine(x, dataArray[i], x, horizontalPositionBefore, 1);
        horizontalPositionBefore = dataArray[i];
        i++;
        // if (x == 0) {
        //     display.clearDisplay();
        // }
    }
    display.display();
}

void drawValues2() {
    getValueSensor = analogRead(sensorPin);
    currentVolt = (getValueSensor * VOLT) / ANALOG_MAX;
    // adapto en pantalla desde 0 a el valor analógico máx que lea (4095 en esp32,1023 en arduino), a la altura de pantalla
    float graficaVoltaje = map(getValueSensor, 0, ANALOG_MAX, SCREEN_HEIGHT - 11, 0);

    horizontalPosition = horizontalPosition % SCREEN_WIDTH;
    // dataArray[horizontalPosition] = (SCREEN_HEIGHT-11) * getValueSensor / ANALOG_MAX;
    dataArray[horizontalPosition] = graficaVoltaje;

    horizontalPosition++;
    byte i = horizontalPosition;
    // Serial.println(analogRead(sensorPin));
    for (int x = 17; x < SCREEN_WIDTH; x++) {
        // Serial.println(i);
        // delay(1000);
        i = i % SCREEN_WIDTH;
        display.drawLine(x, dataArray[i], x, horizontalPositionBefore, 1);
        // display.drawPixel( dataArray[i], 52 - horizontalPositionBefore, WHITE);
        horizontalPositionBefore = dataArray[i];
        i++;
        // if (x == 0) {
        //     display.clearDisplay();
        // }
    }
    display.display();
}

void paintAxes() {
    //dibuja escala. 53/3.3=16    53-16=37   37-16=21    21-16=5
    display.setCursor(0, 5);
    display.print(F("3V"));
    display.setCursor(0, 21);
    display.print(F("2V"));
    display.setCursor(0, 37);
    display.print(F("1V"));

    display.drawLine(15, 5, 17, 5, WHITE);
    display.drawLine(15, 21, 17, 21, WHITE);
    display.drawLine(15, 37, 17, 37, WHITE);

    //dibuja eje X y Y. A partir de 53, dejo espacio para escribir el número.
    display.drawLine(0, 53, 127, 53, WHITE);
    display.drawLine(17, 53, 17, 0, WHITE);
}

void loop() {
    display.clearDisplay();

    paintAxes();

    drawValues2();

    button::loop(36);

    // display.display();
    // if (millis() > 10000 && millis() < 20000) {
    //     sleepDisplay(&display);
    // } else {
    //     wakeDisplay(&display);
    // }
}
