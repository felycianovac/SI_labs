#include "fsm.h"
#include "../../../lab_1/led/led.h"
#include "../../../lab_2/lab_2_1/button/button.h"
#include "../display/display.h"

struct State {
    unsigned long Out;          // Output: LOW or HIGH
    unsigned long Time;         // Delay in units of 10ms
    unsigned long Next[2];      // Next state for [button not pressed, pressed]
};
typedef const struct State SType;

SType FSM[4] = {
    {LOW,  100, {STATE_OFF,   STATE_ON}},     // OFF -> ON
    {HIGH, 100, {STATE_ON,    STATE_BLINK}},  // ON -> BLINK
    {LOW,  50,  {STATE_BLINK, STATE_WAIT}},   // BLINK -> WAIT
    {LOW,  100, {STATE_WAIT,  STATE_OFF}}     // WAIT -> OFF
};

static int currentState = STATE_OFF;
static bool ledState = false;
static unsigned long lastBlink = 0;
static unsigned long lastTransition = 0;
static unsigned long lastInputTime = 0; // NEW: track last valid interaction

void FSM_Init() {
    ledSetup();
    setupButtons();
    ledOff(LED_PIN);
    lastTransition = millis();
    lastBlink = millis();
    lastInputTime = millis(); // track for timeout
    Display_PrintState("OFF");
}

void FSM_Update() {
    unsigned long now = millis(); // Get current time

    // Apply LED output for OFF/ON
    if (currentState == STATE_OFF) {
        ledOff(LED_PIN);
    } else if (currentState == STATE_ON) {
        ledOn(LED_PIN);
    }

    // Blink logic
    if (currentState == STATE_BLINK && now - lastBlink > 500) {
        ledState = !ledState; // Toggle LED state
        if (ledState) ledOn(LED_PIN); else ledOff(LED_PIN);
        lastBlink = now;
    } else if (currentState == STATE_WAIT && now - lastBlink > 1000) {
        ledState = !ledState;
        if (ledState) ledOn(LED_PIN); else ledOff(LED_PIN);
        lastBlink = now;
    }

    // Timeout: return to OFF after 10 seconds of inactivity
    if (currentState != STATE_OFF && now - lastInputTime > 10000) {
        currentState = STATE_OFF;
        ledOff(LED_PIN);
        Display_PrintState("OFF (Timeout)");
        lastTransition = now;
        lastInputTime = now; // prevent repeat
        return;
    }

    // Transition logic
    if (now - lastTransition > FSM[currentState].Time * 10) {
        int input = isButtonPressed(BUTTON1) ? 1 : 0; // Check button state
        int nextState = FSM[currentState].Next[input]; // Get next state

        if (nextState != currentState) { // Only transition if state changes
            currentState = nextState; // Update current state
            lastTransition = now; // Update last transition time
            lastInputTime = now; // track time of valid interaction

            switch (currentState) {
                case STATE_OFF:   Display_PrintState("OFF"); break;
                case STATE_ON:    Display_PrintState("ON"); break;
                case STATE_BLINK: Display_PrintState("BLINK"); break;
                case STATE_WAIT:  Display_PrintState("WAIT"); break;
            }
        }
    }
}
