#include "task_manager.h"
#include "../../../lab_1/led/led.h"
#include "../reporting/reporting.h"
#include "../button/button.h"
#include "../global_states/global_states.h"


// **Task 1: Handle Button LED**
void taskButtonLed() {
    if (isButtonPressed(BUTTON1)) {
        setLed1State(!getLed1State());
        if (getLed1State()) {
            ledOn(RED_LED);
            ledOff(GREEN_LED);  // Turn off blinking LED
        } else {
            ledOff(RED_LED);
        }
    }
}

// **Task 2: Handle Blinking LED (Only if LED1 is OFF)**
void taskBlinkingLed() {
    static unsigned long lastBlinkTime = 0;
    unsigned long currentTime = millis();

    if (!getLed1State() && (currentTime - lastBlinkTime >= getBlinkDelay())) {
        lastBlinkTime = currentTime;
        digitalRead(GREEN_LED) ? ledOff(GREEN_LED) : ledOn(GREEN_LED);
    }
}

// **Task 3: Handle Variable State (Adjust Blink Delay)**
void taskVariableState() {
    if (isButtonPressed(BUTTON2)) {
        int newDelay = getBlinkDelay() + 100;
        if (newDelay > 2000) newDelay = 2000;
        setBlinkDelay(newDelay);
    }
    if (isButtonPressed(BUTTON3)) {
        int newDelay = getBlinkDelay() - 100;
        if (newDelay < 100) newDelay = 100;
        setBlinkDelay(newDelay);
    }
}

// **Task 4: Idle Task (System Reporting)**
void taskIdle() {
    reportSystemState();
    delay(1000);
}
