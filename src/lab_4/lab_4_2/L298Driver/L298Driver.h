#ifndef L298_DRIVER_H
#define L298_DRIVER_H

void L298_Init(int pinIN1, int pinIN2, int pinEN);
void L298_SetDirection(bool forward); // true = înainte, false = înapoi
void L298_SetSpeed(int pwmValue);     // pwmValue = 0..255

#endif
