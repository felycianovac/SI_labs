#ifndef SRV_TASK_MANAGER_H
#define SRV_TASK_MANAGER_H
#include <Arduino_FreeRTOS.h>
#include <queue.h>

typedef struct {
    int setPoint;
    int position;
    int power;
} ReportData;

extern QueueHandle_t queueReporter_;

void Queue_Init();
void PIDControlTask_Init();
void Task_PIDControl(void* pvParameters);
void Task_Reporting(void* pvParameters);

#endif