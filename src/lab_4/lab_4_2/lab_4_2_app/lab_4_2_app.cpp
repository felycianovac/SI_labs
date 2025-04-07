#include <Arduino.h>
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"
#include "../motor/motor_control.h"
#include "../task_manager/task_manager.h"

void lab_4_2_app_setup() {
    service_serial_stdio_setup();
    printf("System started.\r\n");

    Motor_Init(8, 9, 10);  
    TaskManager_Init();   
}

void lab_4_2_app_loop() {
    // Not used with FreeRTOS
}
