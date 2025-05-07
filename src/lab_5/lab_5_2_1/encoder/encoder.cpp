#include "encoder.h"
#include <Arduino.h>

volatile int pulses = 0;
unsigned long lastTime = 0;
int speed = 0;

void encoder_ISR() {
    pulses++;
}

void encoder_init(uint8_t pin) {
    pinMode(pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin), encoder_ISR, CHANGE);
    lastTime = millis();
}

int get_speed() {
    unsigned long now = millis();
    if (now - lastTime >= 100) {
        speed = (pulses * 10); 
        pulses = 0;
        lastTime = now;
    }
    return speed;
}
