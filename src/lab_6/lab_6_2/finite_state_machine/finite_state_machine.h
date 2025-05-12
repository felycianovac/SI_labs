#ifndef FINITE_STATE_MACHINE_H
#define FINITE_STATE_MACHINE_H

#include <Arduino.h>

#define STATE_EW_GREEN         0
#define STATE_EW_YELLOW        1
#define STATE_NS_ENTRY_YELLOW  2
#define STATE_NS_GREEN         3
#define STATE_NS_YELLOW        4
#define STATE_EW_ENTRY_YELLOW  5


typedef struct {
    void (*OutputAction)();
    unsigned long Time;
    int Next[4];
} FSMState;


extern const FSMState FSM[];


#endif
