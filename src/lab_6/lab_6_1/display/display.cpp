#include "display.h"
#include <Arduino.h>


void Display_PrintState(const char* state) {
    printf("FSM State: ");
    printf(state);
    printf("\r\n");
}
