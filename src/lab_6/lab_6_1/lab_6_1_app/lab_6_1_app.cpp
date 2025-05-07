#include "lab_6_1_app.h"
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"
#include "../fsm/fsm.h"
#include "../../../lab_1/led/led.h"
#include "../../../lab_2/lab_2_1/button/button.h"



void lab_6_1_app_setup() {
    service_serial_stdio_setup();
    FSM_Init(); // Initialize the FSM

}

void lab_6_1_app_loop() {
    FSM_Update();
    delay(50); // Add a small delay to avoid busy-waiting

}
