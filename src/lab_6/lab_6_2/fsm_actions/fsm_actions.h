#ifndef FSM_ACTIONS_H
#define FSM_ACTIONS_H

// Called once at startup
void FSM_HW_Init();

void Action_EW_GREEN(void);
void Action_EW_YELLOW(void);
void Action_NS_GREEN(void);
void Action_NS_YELLOW(void);


// Output actions for each FSM state
void Action_NS_RED_TO_YELLOW();
void Action_EW_RED_TO_YELLOW();

void Action_NightModeBlink(void);


#endif
