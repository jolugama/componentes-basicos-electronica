#include <Arduino.h>

//  /*
//  * This is Arduino Sketch for Tutorial video
//  * explaining the 5305 MOSFET used as switch
//  * this sktech turns the MOSFET ON and keeps it ON forever
//  *
//  * Written by Ahmad Shamshiri on Sep 12, 2018 in Ajax, Ontario, Canada
//  * For Robojax.com
//  * Watch instruciton video for this code: https://youtu.be/eAANkWDvusU
//  * This code is "AS IS" without warranty or liability. Free to be used as long as you keep this note intact.
//  */
// byte loadPin =9;// load pin

// void setup() {
//   // Robojax.com demo
//   pinMode(loadPin,OUTPUT);
//   Serial.begin(9600);
//   Serial.println("Robojax Demo");

// }

// void loop() {
//   // Robojax.com  tutorial
//   digitalWrite(loadPin, HIGH);
//  while(1);// wait forever
// }

/*
 * This is Arduino Sketch for Tutorial video 
 * explaining the 5305 MOSFET used as switch 
 * this sktech turns MOSFET ON for 3 seconds then turns it OFF for 3 seconds.
 * 
 * Written by Ahmad Shamshiri on Sep 12, 2018 at 17:36 in Ajax, Ontario, Canada
 * For Robojax.com
 * Watch instruciton video for this code: https://youtu.be/eAANkWDvusU
 * This code is "AS IS" without warranty or liability. Free to be used as long as you keep this note intact.
 */
// int cont = HIGH;
// int loadPin = 9;
// void setup() {
//   // Robojax.com demo
//   pinMode(loadPin,OUTPUT);
//   Serial.begin(9600);
//   Serial.println("Robojax Demo");

// }

// void loop() {
//   // Robojax.com  tutorial

//   if(cont == HIGH)
//   {
//     Serial.println("OUTPUT is HIGH");
//     digitalWrite(loadPin,HIGH);
//     delay(6000);
//     cont = LOW;
//   }else{
//     Serial.println("OUTPUT is LOW");
//     digitalWrite(loadPin,LOW);
//     delay(3000);
//     cont = HIGH;
//   }

// }

//  /*
//  * This is Arduino Sketch for Tutorial video
//  * explaining the 5305 MOSFET used as switch
//  * This sketch will control speed of a motor or intensity of light using PWM
//  *
//  * Written by Ahmad Shamshiri on Sep 12, 2018 at 23:23 in Ajax, Ontario, Canada
//  * For Robojax.com
//  * Watch instruciton video for this code: https://youtu.be/eAANkWDvusU
//  * This code is "AS IS" without warranty or liability. Free to be used as long as you keep this note intact.
//  */
// int motorPin =9;// pin to connect to motor module
// int mSpeed = 0;// variable to hold speed value
// int mStep = 15;// increment/decrement step for PWM motor speed

// void setup() {
//   // Robojax.com demo
//   pinMode(motorPin,OUTPUT);// set mtorPin as output
//   Serial.begin(9600);// initialize serial motor
//   Serial.println("Robojax Demo");

// }

// void loop() {
//   // Robojax.com  tutorial

// analogWrite(motorPin, mSpeed);// send mSpeed value to motor
//     Serial.print("Speed: ");
//     Serial.println(mSpeed);// print mSpeed value on Serial monitor (click on Tools->Serial Monitor)
//   mSpeed = mSpeed + mStep;
//   // See video you for details.
//   if (mSpeed <= 0 || mSpeed >= 255) {
//     mStep = -mStep;
//   }

// delay(200);

// }

byte luzPin = 3;
// int analogPin = A3;
int val = 0;

void setup() {
    Serial.begin(9600);
    pinMode(luzPin, INPUT_PULLUP);
}

void loop() {
    delay(300);
    // val = analogRead(analogPin);
    bool l= digitalRead(luzPin);
    Serial.println(l);
}