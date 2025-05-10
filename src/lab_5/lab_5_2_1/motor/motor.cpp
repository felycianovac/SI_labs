#include "motor.h"
#include <Arduino.h>

static int motorPwmPin = 9;
static int lastPwm = 0;

void Motor_Init(int pwmPin) {
    motorPwmPin = pwmPin;
    pinMode(motorPwmPin, OUTPUT);
}

void Motor_SetSpeed(int pwm) {
    pwm = constrain(pwm, 0, 255); // Constrain PWM value to 0-255
    if (pwm == 0) {
        pinMode(motorPwmPin, OUTPUT); // Set pin mode to OUTPUT to stop the fan
        digitalWrite(motorPwmPin, LOW);  // force it low to stop fan
    } else {
        analogWrite(motorPwmPin, pwm); // Set PWM value to control speed
    }
    lastPwm = pwm; // Store last PWM value for reference
}


int Motor_GetSpeed() {
    return lastPwm;
}