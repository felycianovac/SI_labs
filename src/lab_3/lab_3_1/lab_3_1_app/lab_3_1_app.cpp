#include <Arduino.h>
#include "lab_3_1_app.h"
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"
#include "../sensor/sensor.h"
#include "../display/display.h"
#include "../taskmanager/taskmanager.h"
#include "../../../lab_1/led/led.h"

void lab_3_1_app_setup() {
    ledSetup(); // Initialize LED
    service_serial_stdio_setup();  // Initialize Serial Monitor
    sensor_setup();  // Initialize Sensor
    taskmanager_init();  // Initialize Task Manager

    vTaskStartScheduler(); // Start FreeRTOS Scheduler
}

void lab_3_1_app_loop() {
}
