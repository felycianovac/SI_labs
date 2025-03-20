#include "button.h"

void buttonSetup() {
    // Set the button pin as input with pull-up resistor
    pinMode(BUTTON_PIN, INPUT_PULLUP);

}

bool isButtonPressed() {
    // Check if the button is pressed
    return digitalRead(BUTTON_PIN) == LOW;
}
