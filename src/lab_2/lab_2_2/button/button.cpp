#include "button.h"

void buttonSetup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);

}

bool isButtonPressed() {
    return digitalRead(BUTTON_PIN) == LOW;
}
