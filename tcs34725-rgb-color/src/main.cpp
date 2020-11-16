/**
 * sensor de color tcs34725 mira el color predominante de una tv, y lo copia en un led rgb. 
 */ 
#include <Arduino.h>
#include <Wire.h>

#include "Adafruit_TCS34725.h"

// pines pwm para un arduino mega (led rgb). 
#define redpin 6
#define greenpin 5
#define bluepin 3

// set to false if using a common cathode LED
#define commonAnode false

// our RGB -> eye-recognized gamma color
byte gammatable[256];

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
    Serial.begin(9600);
    //Serial.println("Color View Test!");

    if (tcs.begin()) {
        //Serial.println("Found sensor");
    } else {
        Serial.println("No TCS34725 found ... check your connections");
        while (1)
            ;  // halt!
    }

    // use these three pins to drive an LED
#if defined(ARDUINO_ARCH_ESP32)
    ledcAttachPin(redpin, 1);
    ledcSetup(1, 12000, 8);
    ledcAttachPin(greenpin, 2);
    ledcSetup(2, 12000, 8);
    ledcAttachPin(bluepin, 3);
    ledcSetup(3, 12000, 8);
#else
    pinMode(redpin, OUTPUT);
    pinMode(greenpin, OUTPUT);
    pinMode(bluepin, OUTPUT);
#endif

    // thanks PhilB for this gamma table!
    // it helps convert RGB colors to what humans see
    for (int i = 0; i < 256; i++) {
        float x = i;
        x /= 255;
        x = pow(x, 2.5);
        x *= 255;

        if (commonAnode) {
            gammatable[i] = 255 - x;
        } else {
            gammatable[i] = x;
        }
        //Serial.println(gammatable[i]);
    }
}

// The commented out code in loop is example of getRawData with clear value.
// Processing example colorview.pde can work with this kind of data too, but It requires manual conversion to
// [0-255] RGB value. You can still uncomments parts of colorview.pde and play with clear value.
void loop() {
    float red, green, blue;

    tcs.setInterrupt(false);  // turn on LED

    delay(60);  // takes 50ms to read

    tcs.getRGB(&red, &green, &blue);

    tcs.setInterrupt(true);  // turn off LED

    Serial.print("R:\t");
    Serial.print(int(red));
    Serial.print("\tG:\t");
    Serial.print(int(green));
    Serial.print("\tB:\t");
    Serial.print(int(blue));

    byte rojo = 0;
    byte verde = 0;
    byte azul = 0;
    if (int(red) > 120) {
        rojo = 255;
            Serial.println("rojo");
    } else if (int(red) < 60) {
        rojo = 0;
    }else {
        rojo = int(red);
    }

    if (int(green) > 120) {
        verde = 255;
         Serial.println("verde");
    } else if (int(green) < 60) {
        green = 0;
    } else {
        verde = int(green);
    }

    if (int(blue) > 120) {
        azul = 255;
         Serial.println("azul");
    }  else if (int(blue) < 60) {
        blue = 0;
    }else {
        azul = 0; int(blue);
    }

    Serial.print("\n");

#if defined(ARDUINO_ARCH_ESP32)
    ledcWrite(1, gammatable[(int)red]);
    ledcWrite(2, gammatable[(int)green]);
    ledcWrite(3, gammatable[(int)blue]);
#else
    // analogWrite(redpin, gammatable[(int)red]);
    // analogWrite(greenpin, gammatable[(int)green]);
    // analogWrite(bluepin, gammatable[(int)blue]);

    analogWrite(redpin, rojo);
    analogWrite(greenpin, verde);
    analogWrite(bluepin, azul);

#endif
}