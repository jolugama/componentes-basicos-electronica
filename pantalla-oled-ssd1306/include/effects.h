#include <Adafruit_GFX.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

namespace effects {

// string 21 caracteres máximo
void speak(String frase) {
    const int velocity = 150;
    const byte sizeImage=48;
    for (int i = 0; i < (frase.length() / 6); i++) {
        display.clearDisplay();
        display.drawBitmap((display.width() - sizeImage) / 2, 0, images::sceptic, sizeImage, sizeImage, 1);
        display.setCursor(0, 57);
        display.println(frase);
        display.display();
        delay(velocity);
        display.clearDisplay();
        display.drawBitmap((display.width() - sizeImage) / 2, 0, images::shocked, sizeImage, sizeImage, 1);
        display.setCursor(0, 57);
        display.println(frase);
        display.display();
        delay(velocity);
        display.clearDisplay();
        display.drawBitmap((display.width() - sizeImage) / 2, 0, images::sceptic, sizeImage, sizeImage, 1);
        display.setCursor(0, 57);
        display.println(frase);
        display.display();
        delay(velocity);
        display.clearDisplay();
        display.drawBitmap((display.width() - sizeImage) / 2, 0, images::nervous, sizeImage, sizeImage, 1);
        display.setCursor(0, 57);
        display.println(frase);
        display.display();
        delay(velocity);
        display.clearDisplay();
        display.drawBitmap((display.width() - sizeImage) / 2, 0, images::sceptic, sizeImage, sizeImage, 1);
        display.setCursor(0, 57);
        display.println(frase);
        display.display();
        delay(velocity);
    }
}

void smile(String frase) {
     const byte sizeImage=48;
    display.clearDisplay();
    display.drawBitmap((display.width() - sizeImage) / 2, 0, images::happy, sizeImage, sizeImage, 1);
    display.setCursor(0, 57);
    // display.setTextColor(BLACK, WHITE);  //inverted
    display.println(frase);
    display.display();
}

}  // namespace effects