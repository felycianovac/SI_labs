#include "lab_2_2_app.h"
#include <Arduino.h>
#include "../tasks/task_manager.h"
#include "../../../lab_1/led/led.h"
#include "../button/button.h"
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"
#include "../globals/globals.h"

void lab_2_2_app_setup() {
    service_serial_stdio_setup();
    buttonSetup();
    ledSetup();
    setupSharedResources();

    xTaskCreate(handleButton, "ButtonHandler", TASK_STACK, NULL, TASK_PRIO, NULL);
    xTaskCreate(handleSync, "SyncHandler", TASK_STACK, NULL, TASK_PRIO, NULL);
    xTaskCreate(handleAsync, "AsyncHandler", TASK_STACK, NULL, TASK_PRIO, NULL);

    vTaskStartScheduler();
}
void lab_2_2_app_loop() {
}