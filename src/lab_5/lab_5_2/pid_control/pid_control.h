#ifndef PID_CONTROL_H
#define PID_CONTROL_H

void PIDControl_Init(double p, double i, double d);
void PIDControl_SetInput(double value);
void PIDControl_SetSetpoint(double value);
double PIDControl_GetSetpoint();
double PIDControl_GetOutput();
double PIDControl_Compute();

#endif
