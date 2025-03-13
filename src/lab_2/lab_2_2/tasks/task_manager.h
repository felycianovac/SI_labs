#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <Arduino_FreeRTOS.h>

void handleButton(void* params);
void handleSync(void* params);
void handleAsync(void* params);
bool containsZero(uint8_t number);

#endif // TASK_MANAGER_H
