#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H


void Motor_Init(int pinIN1, int pinIN2, int pinEN);
void Motor_SetPower(int power); // power = -100..100
void Motor_Stop();
int Motor_GetPower();

#endif
