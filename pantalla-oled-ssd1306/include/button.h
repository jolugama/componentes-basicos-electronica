#include <Arduino.h>

namespace button {
byte valor = 0;
byte estado;
byte anterior;  // guardamos el estado anterior.
unsigned long currentMillis;
unsigned long intervalMillis = 50;  // milisegundos que debe pasar pulsando para que se tome como válido
bool screenOn = true;

namespace _private {
void sleepDisplay(Adafruit_SSD1306* display) {
    display->ssd1306_command(SSD1306_DISPLAYOFF);
}

void wakeDisplay(Adafruit_SSD1306* display) {
    display->ssd1306_command(SSD1306_DISPLAYON);
}

}  // namespace _private

void setup(byte pinButton) {
    pinMode(pinButton, INPUT_PULLDOWN);
    valor = HIGH;
    anterior = HIGH;
}

void loop(byte pinButton) {
    if (valor == digitalRead(pinButton)) {
        currentMillis = 0;
    } else if (currentMillis == 0) {
        currentMillis = millis();
    } else if (millis() - currentMillis > intervalMillis) {
        valor = !valor;
    }
    //  Serial.println(digitalRead(valor));
    if (anterior == LOW && valor == LOW) estado = 1;
    if (anterior == LOW && valor == HIGH) estado = 2;
    if (anterior == HIGH && valor == LOW) estado = 3;
    if (anterior == HIGH && valor == HIGH) estado = 4;

    anterior = valor;

    if (estado == 3) {
        screenOn = !screenOn;
        if (screenOn) {
            _private::wakeDisplay(&display);
        } else {
            _private::sleepDisplay(&display);
        }
    }
}

}  // namespace button