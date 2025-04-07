#include "relay.h"
#include <Arduino.h>

static int relayState = 0;

void relaySetup() {
    pinMode(RELAY_PIN, OUTPUT); // Sets the RELAY_PIN as an Output
    digitalWrite(RELAY_PIN, LOW); // Initialize relay to OFF
    relayState = 0; // Set initial state to OFF
}

void relayOn() {
    digitalWrite(RELAY_PIN, HIGH); // Turn on the relay
    relayState = 1; // Update relay state to ON
}

void relayOff() {
    digitalWrite(RELAY_PIN, LOW);
    relayState = 0;
}

int relayGetState() {
    return relayState;
}


