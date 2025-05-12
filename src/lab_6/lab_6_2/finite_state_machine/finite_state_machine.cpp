#include "finite_state_machine.h"
#include "../../lab_6_1/display/display.h"
#include "../../../lab_1/led/led.h"
#include "../fsm_actions/fsm_actions.h"

const FSMState FSM[] = {
    // STATE_EW_GREEN = 0
    { Action_EW_GREEN, 5000, {STATE_EW_GREEN, STATE_EW_YELLOW, STATE_EW_GREEN, STATE_EW_YELLOW} },

    // STATE_EW_YELLOW = 1 (EW exiting green)
    { Action_EW_YELLOW, 2000, {STATE_NS_ENTRY_YELLOW, STATE_NS_ENTRY_YELLOW, STATE_NS_ENTRY_YELLOW, STATE_NS_ENTRY_YELLOW} },

    // STATE_NS_ENTRY_YELLOW = 2 (NS preparing green)
    { Action_NS_RED_TO_YELLOW, 2000, {STATE_NS_GREEN, STATE_NS_GREEN, STATE_NS_GREEN, STATE_NS_GREEN} },

    // STATE_NS_GREEN = 3
    { Action_NS_GREEN, 5000, {STATE_NS_GREEN, STATE_NS_YELLOW, STATE_NS_GREEN, STATE_NS_YELLOW} },

    // STATE_NS_YELLOW = 4 (NS exiting green)
    { Action_NS_YELLOW, 2000, {STATE_EW_ENTRY_YELLOW, STATE_EW_ENTRY_YELLOW, STATE_EW_ENTRY_YELLOW, STATE_EW_ENTRY_YELLOW} },

    // STATE_EW_ENTRY_YELLOW = 5 (EW preparing green)
    { Action_EW_RED_TO_YELLOW, 2000, {STATE_EW_GREEN, STATE_EW_GREEN, STATE_EW_GREEN, STATE_EW_GREEN} }
};
