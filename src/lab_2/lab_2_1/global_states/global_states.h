#ifndef GLOBAL_STATES_H
#define GLOBAL_STATES_H

#include <Arduino.h>

// **Global States**
struct GlobalState {
    bool led1State;     // LED1 (RED) state
    int blinkDelay;     // LED2 blinking interval
};

// **Functions to Access Global States**
void initGlobalState();
bool getLed1State();
void setLed1State(bool state);
int getBlinkDelay();
void setBlinkDelay(int delay);

#endif
