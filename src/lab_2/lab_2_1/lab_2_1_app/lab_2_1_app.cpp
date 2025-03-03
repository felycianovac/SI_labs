#include "lab_2_1_app.h"
#include "../button/button.h"
#include "../reporting/reporting.h"
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"
#include "../../../lab_1/led/led.h"
#include "../task_manager/task_manager.h"
#include "../srv_timer/srv_timer.h"
#include "../global_states/global_states.h"

void lab_2_1_app_setup() {
    initGlobalState();  // Initialize global state variables
    service_serial_stdio_setup(); // Serial communication setup
    ledSetup();  // Initialize LEDs
    setupButtons();  // Initialize buttons
    setupTimer1();   // Start Timer1-based scheduler
    printf("APP Lab 2.1 Started\n");
}
void lab_2_1_app_loop() {

}
