#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

#define BUTTON1 2
#define BUTTON2 4
#define BUTTON3 3

void setupButtons();
bool isButtonPressed(int buttonPin);

#endif
