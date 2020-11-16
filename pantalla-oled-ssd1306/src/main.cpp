#include <Adafruit_I2CDevice.h>
#include <Arduino.h>

/**************************************************************************
128x64 pixel display using I2C to communicate
 **************************************************************************/

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 4  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES 10  // Number of snowflakes in the animation example

#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16
static const unsigned char PROGMEM logo_bmp[] =
    {B00000000, B11000000,
     B00000001, B11000000,
     B00000001, B11000000,
     B00000011, B11100000,
     B11110011, B11100000,
     B11111110, B11111000,
     B01111110, B11111111,
     B00110011, B10011111,
     B00011111, B11111100,
     B00001101, B01110000,
     B00011011, B10100000,
     B00111111, B11100000,
     B00111111, B11110000,
     B01111100, B11110000,
     B01110000, B01110000,
     B00000000, B00110000};

byte x = 0;
byte sensor = 36;
int lecturaSensor = 0;

byte data[128];  // para guardar las lecturas
byte indexs = 0;
byte anterior;

// void testdrawstyles(void) {
//   display.clearDisplay();

//   display.setTextSize(1);             // Normal 1:1 pixel scale
//   display.setTextColor(SSD1306_WHITE);        // Draw white text
//   display.setCursor(0,0);             // Start at top-left corner
//   display.println(F("Hello, world!"));

//   display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
//   display.println(3.141592);

//   display.setTextSize(2);             // Draw 2X-scale text
//   display.setTextColor(SSD1306_WHITE);
//   display.print(F("0x")); display.println(0xDEADBEEF, HEX);

//   display.display();
//   delay(2000);
// }

void testscrolltext(void) {
    display.clearDisplay();

    display.setTextSize(4);  // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(300, 0);
    display.println(F("JoLuGaMa"));
    display.display();  // Show initial text
    delay(100);

    // Scroll in various directions, pausing in-between:
    display.startscrollright(0x00, 0x0F);
    delay(2000);
    display.stopscroll();
    delay(1000);
    display.startscrollleft(0x00, 0x0F);
    delay(2000);
    display.stopscroll();
    delay(1000);
    display.startscrolldiagright(0x00, 0x07);
    delay(2000);
    display.startscrolldiagleft(0x00, 0x07);
    delay(2000);
    display.stopscroll();
    delay(1000);
}

void testdrawbitmap(void) {
    display.clearDisplay();

    display.drawBitmap(
        (display.width() - LOGO_WIDTH) / 2,
        (display.height() - LOGO_HEIGHT) / 2,
        logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
    display.display();
    delay(1000);
}

#define XPOS 0  // Indexes into the 'icons' array in function below
#define YPOS 1
#define DELTAY 2

void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
    int8_t f, icons[NUMFLAKES][3];

    // Initialize 'snowflake' positions
    for (f = 0; f < NUMFLAKES; f++) {
        icons[f][XPOS] = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS] = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
        Serial.print(F("x: "));
        Serial.print(icons[f][XPOS], DEC);
        Serial.print(F(" y: "));
        Serial.print(icons[f][YPOS], DEC);
        Serial.print(F(" dy: "));
        Serial.println(icons[f][DELTAY], DEC);
    }

    for (;;) {                   // Loop forever...
        display.clearDisplay();  // Clear the display buffer

        // Draw each snowflake:
        for (f = 0; f < NUMFLAKES; f++) {
            display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
        }

        display.display();  // Show the display buffer on the screen
        delay(200);         // Pause for 1/10 second

        // Then update coordinates of each flake...
        for (f = 0; f < NUMFLAKES; f++) {
            icons[f][YPOS] += icons[f][DELTAY];
            // If snowflake is off the bottom of the screen...
            if (icons[f][YPOS] >= display.height()) {
                // Reinitialize to a random position, just off the top
                icons[f][XPOS] = random(1 - LOGO_WIDTH, display.width());
                icons[f][YPOS] = -LOGO_HEIGHT;
                icons[f][DELTAY] = random(1, 6);
            }
        }
    }
}

void setup() {
    Serial.begin(115200);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3C for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;  // Don't proceed, loop forever
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

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.clearDisplay();
    for (int i = 0; i < 128; i++) {
        data[i] = 0;
    }
}

void loop() {
  analogSetWidth(12); // 10 bits son los que usa arduino.
  // analogSetAttenuation(ADC_11db);
  analogSetPinAttenuation(36,ADC_11db); // es el máximo, se acerca al de arduino.
  display.clearDisplay();
  indexs = indexs %128;
  lecturaSensor= analogRead(sensor);
  data[indexs]=64*lecturaSensor /4096; // es por los 11 bit. cambiar a automático.
  indexs++;
  byte i= indexs;
  Serial.println(analogRead(36));
  for(int x= 0; x<128; x++){
    i=i%128;
    display.drawLine(x,data[i],x,anterior,1);
    anterior= data[i];
    i++;
    if(x==0){
      display.clearDisplay();
    }
  }
  display.display();
}
