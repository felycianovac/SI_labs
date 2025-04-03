#include "relay.h"
#include <Arduino.h>

static int relayState = 0;

void relaySetup() {
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);
    relayState = 0;
}

void relayOn() {
    digitalWrite(RELAY_PIN, HIGH);
    relayState = 1;
}

void relayOff() {
    digitalWrite(RELAY_PIN, LOW);
    relayState = 0;
}

int relayGetState() {
    return relayState;
}


