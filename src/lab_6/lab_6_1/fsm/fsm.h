#ifndef FSM_H
#define FSM_H

#define LED_PIN 13

#define STATE_OFF   0
#define STATE_ON    1
#define STATE_BLINK 2
#define STATE_WAIT  3

void FSM_Init();
void FSM_Update();
#endif // FSM_H