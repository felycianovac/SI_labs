#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

#define BUTTON_PIN 11

// Button Functions
void buttonSetup();
bool isButtonPressed();

#endif // BUTTON_H
