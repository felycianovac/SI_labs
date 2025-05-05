#include <Arduino.h>
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"
#include "../pid_control/pid_control.h"
#include "../../lab_5_1/sensor/potentiometer.h"
#include "../../../lab_2/lab_2_1/button/button.h"
#include "../../../lab_4/lab_4_2/motor/motor_control.h"
#include "../../../lab_1/led/led.h"
#include <Arduino_FreeRTOS.h>
#include "../task_manager_srv/task_manager_srv.h"

void lab_5_2_app_setup() {
    service_serial_stdio_setup();
    printf("System started.\r\n");
    ledSetup(); 
    
    Motor_Init(8, 9, 10);  
    

    ReportQueue_Init(); 
    PIDControl_Init(2.0, 0.5, 1.0); 
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
