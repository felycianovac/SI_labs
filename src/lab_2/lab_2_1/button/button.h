#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 4

void setupButtons();
bool isButtonPressed(int buttonPin);

#endif
