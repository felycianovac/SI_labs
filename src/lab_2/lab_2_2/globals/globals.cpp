#include "globals.h"

SemaphoreHandle_t buttonTrigger = NULL;
QueueHandle_t numberQueue = NULL;
SemaphoreHandle_t counterLock = NULL;
SemaphoreHandle_t serialLock = NULL;
uint8_t buttonPresses = 0;

void setupSharedResources() {
    // Create shared resources
    // Create a semaphore to trigger the button task
    buttonTrigger = xSemaphoreCreateBinary();
    // Create a queue to store numbers
    numberQueue = xQueueCreate(QUEUE_CAPACITY, sizeof(uint8_t));
    // Create a semaphore to lock the counter
    counterLock = xSemaphoreCreateMutex();
    // Create a semaphore to lock the serial port
    serialLock = xSemaphoreCreateMutex();
}