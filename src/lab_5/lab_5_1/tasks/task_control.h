#ifndef TASK_CONTROL_H
#define TASK_CONTROL_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>

typedef struct {
    int setPoint;
    int position;
    int power;
} ReportData;

extern QueueHandle_t queueReport;

void ControlTask_Init();
void Task_ControlLoop(void* pvParameters);
void Task_Reporter(void* pvParameters);

#endif
