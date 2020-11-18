#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_SSD1306.h>

namespace osciloscope {
byte x = 0;
int getValueSensor = 0;

byte dataArray[SCREEN_WIDTH];
byte horizontalPosition = 0;
byte horizontalPositionBefore;
float currentVolt;

void drawValues() {
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

}  // namespace osciloscope