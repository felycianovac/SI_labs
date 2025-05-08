#include "motor.h"
#include <Arduino.h>

static int motorPwmPin = 9;
static int lastPwm = 0;

void Motor_Init(int pwmPin) {
    motorPwmPin = pwmPin;
    pinMode(motorPwmPin, OUTPUT);
}

void Motor_SetSpeed(int pwm) {
    pwm = constrain(pwm, 0, 255);
    analogWrite(motorPwmPin, pwm);
    lastPwm = pwm;
}

int Motor_GetSpeed() {
    return lastPwm;
}