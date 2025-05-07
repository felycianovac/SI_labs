#include "pid_control.h"
#include <Arduino.h>

static double input = 0;
static double output = 0;
static double setpoint = 512;

static double kp = 0.5, ki = 0.05, kd = 0.1;

static double previousError = 0;
static double integral = 0;

static unsigned long lastTime = 0;

void PIDControl_Init(double p, double i, double d) {
    kp = p;
    ki = i;
    kd = d;
    lastTime = millis();
    integral = 0;
    previousError = 0;
}

void PIDControl_SetInput(double value) {
    input = value;
}

void PIDControl_SetSetpoint(double value) {
    setpoint = value;
}

double PIDControl_GetSetpoint() {
    return setpoint;
}

double PIDControl_GetOutput() {
    return output;
}

double PIDControl_Compute() {
    unsigned long now = millis(); // Get current time in milliseconds
    double dt = (now - lastTime) / 1000.0; // Convert to seconds
    if (dt <= 0.001) dt = 0.001; 

    double error = setpoint - input;

    // --- INTEGRAL with anti-windup based on output limits ---
    double potentialIntegral = integral + error * dt; // Calculate potential integral
    double potentialOutput = kp * error + ki * potentialIntegral + kd * (error - previousError) / dt; // Calculate potential output

    if (potentialOutput > 255 || potentialOutput < -255) {
        // Don't update integral to avoid wind-up
    } else {
        integral = potentialIntegral;
    }

    // --- DERIVATIVE ---
    double derivative = (error - previousError) / dt;

    // --- PID FORMULA ---
    output = kp * error + ki * integral + kd * derivative;

    // Clamp output
    if (output > 255) output = 255;
    if (output < -255) output = -255;

    // Save state
    previousError = error;
    lastTime = now;

    return output;
}

