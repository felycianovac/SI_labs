#include "motor_control.h"
#include "../L298Driver/L298Driver.h"
#include <Arduino.h>

static int currentPower = 0;

void Motor_Init(int pinIN1, int pinIN2, int pinEN) {
    L298_Init(pinIN1, pinIN2, pinEN); // Initialize the L298 driver
    Motor_Stop(); // Stop the motor initially
}

void Motor_SetPower(int power) {
    currentPower = constrain(power, -100, 100); // Constrain power to the range -100 to 100
    bool forward = currentPower >= 0; // Determine direction based on power sign
    L298_SetDirection(forward); // Set motor direction
    L298_SetSpeed(map(abs(currentPower), 0, 100, 0, 255)); // Set speed based on power
}

void Motor_Stop() {
    Motor_SetPower(0); // Stop the motor by setting power to 0
}

int Motor_GetPower() {
    return currentPower; // Return the current power setting
}
