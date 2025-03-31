#ifndef LED_H
#define LED_H

#define GREEN_LED 12  // Define Green LED pin
#define RED_LED 13    // Define Red LED pin

void ledSetup();
void ledOn(int ledPin);
void ledOff(int ledPin);

#endif