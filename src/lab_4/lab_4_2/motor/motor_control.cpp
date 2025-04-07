#include "motor_control.h"
#include "../L298Driver/L298Driver.h"
#include <Arduino.h>

static int currentPower = 0;

void Motor_Init(int pinIN1, int pinIN2, int pinEN) {
    L298_Init(pinIN1, pinIN2, pinEN);
    Motor_Stop();
}

void Motor_SetPower(int power) {
    currentPower = constrain(power, -100, 100);
    bool forward = currentPower >= 0;
    L298_SetDirection(forward);
    L298_SetSpeed(map(abs(currentPower), 0, 100, 0, 255));
}

void Motor_Stop() {
    Motor_SetPower(0);
}

int Motor_GetPower() {
    return currentPower;
}
