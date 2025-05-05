#ifndef TASK_MANAGER_SRV_H
#define TASK_MANAGER_SRV_H

#include "Arduino_FreeRTOS.h"
#include "queue.h"

typedef struct {
    int setPoint;
    int position;
    int power;
} ReportData;

extern QueueHandle_t queueReporter;

void Task_PID_Control(void* pvParameters);
void Task_ReportPlot(void* pvParameters);
void TaskManager_InitTasks();
void ReportQueue_Init();

#endif
