#include <Arduino.h>
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"
#include "../../../lab_4/lab_4_2/motor/motor_control.h"
#include "../tasks/task_control.h"
#include <Arduino_FreeRTOS.h>

void lab_5_1_app_setup() {
    service_serial_stdio_setup();
    printf("System started.\r\n");
    ControlTask_Init();


    Motor_Init(8, 9, 10);  
    xTaskCreate(Task_ControlLoop, "ControlTask", 512, NULL, 1, NULL);
    xTaskCreate(Task_Reporter, "ReportTask", 512, NULL, 1, NULL);
}


void lab_5_1_app_loop() {
    // Not used with FreeRTOS
}
