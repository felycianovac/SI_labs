#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <Arduino_FreeRTOS.h>
#include <queue.h>  


// Shared queue for display data
extern QueueHandle_t displayQueue;

// Starts all tasks (joystick + display)
void start_tasks();

#endif
