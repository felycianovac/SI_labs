#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>

typedef enum {
    CMD_NONE,
    CMD_RELAY_ON,
    CMD_RELAY_OFF
} RelayCommand;

extern QueueHandle_t commandQueue;

#endif
