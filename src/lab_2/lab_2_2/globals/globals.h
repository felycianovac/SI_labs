#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>

#define TASK_STACK 128
#define TASK_PRIO 1

#define BUTTON_CHECK_INTERVAL 10
#define GREEN_LED_DURATION 1000
#define RED_LED_ON_TIME 300
#define RED_LED_OFF_TIME 500
#define SYNC_TASK_WAIT 50
#define ASYNC_TASK_WAIT 200

#define QUEUE_CAPACITY 20

extern SemaphoreHandle_t buttonTrigger;
extern QueueHandle_t numberQueue;
extern SemaphoreHandle_t counterLock;
extern SemaphoreHandle_t serialLock;

extern uint8_t buttonPresses;

void setupSharedResources();

#endif