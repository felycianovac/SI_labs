#include <Arduino.h>
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"
#include "../pid_control/pid_control.h"
#include "../../lab_5_1/sensor/potentiometer.h"
#include "../../../lab_2/lab_2_1/button/button.h"
#include "../report_queue/report_queue.h"
#include "../task_reporter/task_reporter.h"
#include "../task_pid_control/task_pid_control.h"
#include "../../../lab_4/lab_4_2/motor/motor_control.h"
#include "../../../lab_1/led/led.h"
#include <Arduino_FreeRTOS.h>

void lab_5_2_app_setup() {
    service_serial_stdio_setup();
    printf("System started.\r\n");
    ledSetup(); // Initialize the LED
    
    Motor_Init(8, 9, 10);  
    

    ReportQueue_Init(); // Initialize the report queue
    PIDControl_Init(2.0, 0.5, 1.0); // Initialize PID control with Kp, Ki, Kd values
    potentiometer_init(A0);
    setupButtons();

    xTaskCreate(
        Task_PID_Control,     // Task function
        "PID_Control",        // Name
        256,                  // Stack size (words, not bytes on AVR)
        NULL,                 // Parameters
        2,                    // Priority
        NULL                  // Task handle (not needed here)
    );

    // Create reporter task
    xTaskCreate(
        Task_ReportPlot,
        "Report",
        256,
        NULL,
        1,
        NULL
    );

}


void lab_5_2_app_loop() {
    // Not used with FreeRTOS
}
