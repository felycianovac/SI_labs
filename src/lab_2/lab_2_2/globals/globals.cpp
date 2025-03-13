#include "globals.h"

SemaphoreHandle_t buttonTrigger = NULL;
QueueHandle_t numberQueue = NULL;
SemaphoreHandle_t counterLock = NULL;
SemaphoreHandle_t serialLock = NULL;
uint8_t buttonPresses = 0;

void setupSharedResources() {
    buttonTrigger = xSemaphoreCreateBinary();
    numberQueue = xQueueCreate(QUEUE_CAPACITY, sizeof(uint8_t));
    counterLock = xSemaphoreCreateMutex();
    serialLock = xSemaphoreCreateMutex();
}