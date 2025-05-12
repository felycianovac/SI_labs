#include "fsm_actions.h"
#include "../../../lab_1/led/led.h"
#include "../../../lab_2/lab_2_1/button/button.h"
#include "../globals/globals.h"
#include "../../lab_6_1/display/display.h"


void FSM_HW_Init() {
    ledSetup();
    setupButtons();
}

// Custom action function for EW Red to Yellow transition
void Action_EW_RED_TO_YELLOW() {
    ledOn(LED_EW_YELLOW);
    ledOn(LED_NS_RED);

    //make sure all LEDs are off
    ledOff(LED_EW_GREEN);
    ledOff(LED_NS_YELLOW);
    ledOff(LED_NS_GREEN);
    ledOff(LED_EW_RED);

    Display_PrintState("EW RED TO YELLOW");
}

// Custom action function for NS Red to Yellow transition
void Action_NS_RED_TO_YELLOW() {
    ledOn(LED_NS_YELLOW);
    ledOn(LED_EW_RED);

    //make sure all LEDs are off
    ledOff(LED_EW_YELLOW);
    ledOff(LED_NS_GREEN);
    ledOff(LED_NS_RED);
    ledOff(LED_EW_GREEN);

    Display_PrintState("NS RED TO YELLOW");
}

void Action_EW_GREEN() {
    ledOn(LED_EW_GREEN);
    ledOn(LED_NS_RED);

    //make sure all LEDs are off
    ledOff(LED_EW_YELLOW);
    ledOff(LED_NS_YELLOW);
    ledOff(LED_NS_GREEN);
    ledOff(LED_EW_RED);

    Display_PrintState("EW GREEN");
}

// State: East-West YELLOW, North-South RED
void Action_EW_YELLOW() {
    ledOn(LED_EW_YELLOW);
    ledOn(LED_NS_RED);

    //make sure all LEDs are off
    ledOff(LED_EW_GREEN);
    ledOff(LED_NS_YELLOW);
    ledOff(LED_NS_GREEN);
    ledOff(LED_EW_RED);

    Display_PrintState("EW YELLOW");
}

// State: North-South GREEN, East-West RED
void Action_NS_GREEN() {
    ledOn(LED_NS_GREEN);
    ledOn(LED_EW_RED);

    //make sure all LEDs are off
    ledOff(LED_EW_YELLOW);
    ledOff(LED_NS_YELLOW);
    ledOff(LED_NS_RED);
    ledOff(LED_EW_GREEN);

    Display_PrintState("NS GREEN");
}

// State: North-South YELLOW, East-West RED
void Action_NS_YELLOW() {
    ledOn(LED_NS_YELLOW);
    ledOn(LED_EW_RED);

    //make sure all LEDs are off
    ledOff(LED_EW_YELLOW);
    ledOff(LED_NS_GREEN);
    ledOff(LED_NS_RED);
    ledOff(LED_EW_GREEN);
    
    Display_PrintState("NS YELLOW");
}

void Action_NightModeBlink() {
    static bool yellowState = false;

    if (yellowState) {
        ledOff(LED_EW_GREEN);
        ledOff(LED_NS_GREEN);
        ledOff(LED_EW_RED);
        ledOff(LED_NS_RED);
        
        ledOff(LED_EW_YELLOW);
        ledOff(LED_NS_YELLOW);
    } else {
        ledOn(LED_EW_YELLOW);
        ledOn(LED_NS_YELLOW);
    }

    yellowState = !yellowState;
}
