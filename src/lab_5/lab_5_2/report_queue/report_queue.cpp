#include "report_queue.h"

QueueHandle_t queueReporter = NULL;

void ReportQueue_Init() {
    queueReporter = xQueueCreate(5, sizeof(ReportData));
}
