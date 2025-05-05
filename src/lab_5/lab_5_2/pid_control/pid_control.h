#ifndef PID_CONTROL_H
#define PID_CONTROL_H

void PIDControl_Init(double kp, double ki, double kd);
void PIDControl_SetInput(double value);
void PIDControl_SetSetpoint(double value);
double PIDControl_Compute(); // returns output
double PIDControl_GetOutput();
double PIDControl_GetSetpoint();


#endif
