#include "lab_4_1_app.h"
#include <Arduino.h>
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"
#include "../tasks/task_manager.h"
#include "../relay/relay.h"
#include "../../../lab_1/led/led.h"
#include <Arduino_FreeRTOS.h>   



void lab_4_1_app_setup() {
    service_serial_stdio_setup();
    relaySetup();
    ledSetup();

    printf("Relay and LED setup complete.\r\n");
    printf("Commands: relay on / relay off\r\n");

    TaskManager_StartTasks();  
    vTaskStartScheduler();

}

void lab_4_1_app_loop() {
    // Empty loop, all tasks are handled by FreeRTOS
}