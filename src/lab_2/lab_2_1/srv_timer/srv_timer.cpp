#include "srv_timer.h"
#include "../task_manager/task_manager.h"

void setupTimer1() {
    noInterrupts();

    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS11) | (1 << CS10);
    OCR1A = 2499;
    TIMSK1 |= (1 << OCIE1A);

    interrupts();
}

// Timer1 ISR (Every 10ms)
ISR(TIMER1_COMPA_vect) {
    static int buttonTaskCounter = 5;  // Every 50ms
    static int blinkingTaskCounter = 20; // Every 200ms
    static int variableStateCounter = 10; // Every 100ms
    
    if (--buttonTaskCounter <= 0) {
        buttonTaskCounter = 5;
        taskButtonLed();
    }

    if (--blinkingTaskCounter <= 0) {
        blinkingTaskCounter = 20;
        taskBlinkingLed();
    }

    if (--variableStateCounter <= 0) {
        variableStateCounter = 10;
        taskVariableState();
    }
}
