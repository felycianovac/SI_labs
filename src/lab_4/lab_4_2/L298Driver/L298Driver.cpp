#include "L298Driver.h"
#include <Arduino.h>

static int in1, in2, en;

void L298_Init(int pinIN1, int pinIN2, int pinEN) {
    in1 = pinIN1;
    in2 = pinIN2;
    en = pinEN;
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(en, OUTPUT);
}

void L298_SetDirection(bool forward) {
    digitalWrite(in1, forward ? HIGH : LOW);
    digitalWrite(in2, forward ? LOW : HIGH);
}

void L298_SetSpeed(int pwmValue) {
    analogWrite(en, constrain(pwmValue, 0, 255));
}
