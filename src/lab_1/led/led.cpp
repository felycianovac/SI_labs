#include "led.h"
#include <Arduino.h>

// LED pin
void ledSetup() {
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
}
// Turn on the LED
void ledOn(int ledPin) {
    digitalWrite(ledPin, HIGH);
}
// Turn off the LED
void ledOff(int ledPin) {
    digitalWrite(ledPin, LOW);
}