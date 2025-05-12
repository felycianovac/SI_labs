#include "led.h"
#include <Arduino.h>
#include "../../lab_6/lab_6_2/globals/globals.h"

// LED pin
void ledSetup() {
    // // Set the LED pins as outputs
    // pinMode(GREEN_LED, OUTPUT);

    // pinMode(RED_LED, OUTPUT);

    pinMode(LED_EW_GREEN, OUTPUT);
    pinMode(LED_EW_YELLOW, OUTPUT);
    pinMode(LED_NS_GREEN, OUTPUT);
    pinMode(LED_NS_YELLOW, OUTPUT);
    pinMode(LED_EW_RED, OUTPUT);
    pinMode(LED_NS_RED, OUTPUT);


}
// Turn on the LED
void ledOn(int ledPin) {
    digitalWrite(ledPin, HIGH);
}
// Turn off the LED
void ledOff(int ledPin) {
    digitalWrite(ledPin, LOW);
}