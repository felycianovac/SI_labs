#include "global_states.h"

// **Global State Instance**
static GlobalState globalState;

void initGlobalState() {
    globalState.led1State = false;  // LED1 initially OFF
    globalState.blinkDelay = 500;   // Default blinking delay
}

// **Getters and Setters for Global Variables**
bool getLed1State() {
    return globalState.led1State;
}

void setLed1State(bool state) {
    globalState.led1State = state;
}

int getBlinkDelay() {
    return globalState.blinkDelay;
}

void setBlinkDelay(int delay) {
    if (delay >= 100 && delay <= 2000) {  // Ensure valid range
        globalState.blinkDelay = delay;
    }
}
