#include "reporting.h"
#include <stdio.h>
#include "../global_states/global_states.h"

void reportSystemState() {
    printf("LED1: %s | LED2 Blinking: %s | Blink Delay: %d ms\n",
           getLed1State() ? "ON" : "OFF",
           getLed1State() ? "NO" : "YES",
           getBlinkDelay());
}
