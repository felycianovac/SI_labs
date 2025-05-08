#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

void Motor_Init(int pwmPin);
void Motor_SetSpeed(int pwm);
int Motor_GetSpeed();

#endif