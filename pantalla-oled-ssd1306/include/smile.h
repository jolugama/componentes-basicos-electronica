namespace smile {

// string 21 caracteres máximo
void speak(String frase) {
    
    const int velocity = 150;
    for (int i = 0; i < (frase.length() / 6); i++) {
        display.clearDisplay();
        display.drawBitmap((display.width() - 48) / 2, 0, images::sceptic, 48, 48, 1);
        display.setCursor((display.width() / 2)-frase.length()*2, 57);
        display.println(frase);
        display.display();
        delay(velocity);
        display.clearDisplay();
        display.drawBitmap((display.width() - 48) / 2, 0, images::shocked, 48, 48, 1);
         display.setCursor((display.width() / 2)-frase.length()*2, 57);
        display.println(frase);
        display.display();
        delay(velocity);
        display.clearDisplay();
        display.drawBitmap((display.width() - 48) / 2, 0, images::sceptic, 48, 48, 1);
         display.setCursor((display.width() / 2)-frase.length()*2, 57);
        display.println(frase);
        display.display();
        delay(velocity);
        display.clearDisplay();
        display.drawBitmap((display.width() - 48) / 2, 0, images::nervous, 48, 48, 1);
         display.setCursor((display.width() / 2)-frase.length()*2, 57);
        display.println(frase);
        display.display();
        delay(velocity);
    }
}

void smile(String frase) {
    display.clearDisplay();
    display.drawBitmap((display.width() - 48) / 2, 0, images::happy, 48, 48, 1);
    display.setCursor(0, 57);
    // display.setTextColor(BLACK, WHITE);  //inverted
    display.println(frase);
    display.display();
}

}  // namespace speak