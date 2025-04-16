#include "potentiometer.h"
#include <Arduino.h>

static int sensorPin;

void potentiometer_init(int pin) {
    sensorPin = pin;
    pinMode(sensorPin, INPUT);
}

int potentiotemeter_readPosition() {
    return analogRead(sensorPin); // 0–1023 range
}
