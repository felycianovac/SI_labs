#include "task_reporter.h"
#include "../report_queue/report_queue.h"
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"

void Task_ReportPlot(void* pvParameters) {

    ReportData data;

    while (true) {
        if (xQueueReceive(queueReporter, &data, portMAX_DELAY) == pdPASS) {
            printf("SetPoint: %d\tPosition: %d\tOutput: %d\n",
                   data.setPoint, data.position, data.power);
        }

        vTaskDelay(pdMS_TO_TICKS(500));  
    }
}
