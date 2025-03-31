#include <Arduino.h>
#include "lab_3_2_app.h"
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"
#include "../sensor/joystick_sensor.h"
#include "../tasks/task_manager.h"
#include "../display/display.h"

void lab_3_2_app_setup() {
    // Initialize serial communication
    service_serial_stdio_setup();

    sensor_init();  

    display_init();

    start_tasks();     // Starts both joystick + display tasks

    vTaskStartScheduler();
}

void lab_3_2_app_loop() {
}
