#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <Arduino_FreeRTOS.h>
#include "semphr.h"
#include "queue.h"

extern QueueHandle_t sensorQueue;  
extern SemaphoreHandle_t sensorSemaphore;  // Declare semaphore


void taskmanager_init(); // Function to initialize tasks

#endif
