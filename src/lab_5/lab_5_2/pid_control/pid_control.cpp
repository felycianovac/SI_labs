// pid_control.cpp
#include "pid_control.h"
#include <PID_v1.h>

// Variables used by PID library
static double input = 0;
static double output = 0;
static double setpoint = 2000;

static double kp = 2.0, ki = 0.5, kd = 1.0;

// Create PID instance
static PID fanPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

void PIDControl_Init(double p, double i, double d) {
    kp = p;
    ki = i;
    kd = d;
    fanPID.SetTunings(kp, ki, kd);
    fanPID.SetOutputLimits(0, 255); // minimum threshold to ensure fan spins
    fanPID.SetMode(AUTOMATIC);
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
    fanPID.Compute();
    return output;
}
