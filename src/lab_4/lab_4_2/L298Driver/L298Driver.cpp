#include "L298Driver.h"
#include <Arduino.h>

static int in1, in2, en;

void L298_Init(int pinIN1, int pinIN2, int pinEN) {
    in1 = pinIN1; // Set the IN1 pin
    in2 = pinIN2; // Set the IN2 pin
    en = pinEN; // Set the EN pin
    pinMode(in1, OUTPUT); // Set IN1 as output
    pinMode(in2, OUTPUT);// Set IN2 as output
    pinMode(en, OUTPUT);// Set EN as output
}

void L298_SetDirection(bool forward) {
    digitalWrite(in1, forward ? HIGH : LOW); // Set IN1 to HIGH or LOW based on direction
    digitalWrite(in2, forward ? LOW : HIGH); // Set IN2 to LOW or HIGH based on direction
}

void L298_SetSpeed(int pwmValue) {
    analogWrite(en, constrain(pwmValue, 0, 255)); // Set the EN pin to pwmValue (0-255)
}
