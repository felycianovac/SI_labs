#ifndef REPORT_QUEUE_H
#define REPORT_QUEUE_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>

struct ReportData {
    int setPoint;
    int position;
    int power;
};

extern QueueHandle_t queueReporter;

void ReportQueue_Init();

#endif
