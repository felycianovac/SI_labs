#include "lab_6_2_app.h"
#include <Arduino.h>
#include "../task_manager/task_manager_srv.h"
#include "../fsm_actions/fsm_actions.h"
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"

void lab_6_2_app_setup() {
    FSM_HW_Init(); 
    service_serial_stdio_setup();
    
    TaskManager_Initialize();
}

void lab_6_2_app_loop() {
    // Optional: can leave empty if you use FreeRTOS tasks only
}
