#include "button.h"
#include "../../../lab_6/lab_6_2/globals/globals.h"

void setupButtons() {
    // Set button pins as input
    // pinMode(BUTTON1, INPUT_PULLUP);
    // pinMode(BUTTON2, INPUT_PULLUP);
    // pinMode(BUTTON3, INPUT_PULLUP);
    pinMode(BUTTON_NS_REQUEST, INPUT_PULLUP);
    pinMode(BUTTON_NIGHTMODE, INPUT_PULLUP);
}


bool isButtonPressed(int buttonPin) {
    static unsigned long lastPressTime[3] = {0, 0, 0}; // Last press time for each button
    unsigned long currentTime = millis(); // Current time in ms
    
    // int buttonIndex = (buttonPin == BUTTON1) ? 0 : (buttonPin == BUTTON2) ? 1 : 2; // Get button index
       int buttonIndex = (buttonPin == BUTTON_NS_REQUEST) ? 0 : 1; // Get button index
    
    // Check if button is pressed and debounce
    if (digitalRead(buttonPin) == LOW && (currentTime - lastPressTime[buttonIndex]) > 50) {  // 50ms debounce
        // Update last press time
        lastPressTime[buttonIndex] = currentTime;
        // Return true if button is pressed
        return true;
    }
    // Return false if button is not pressed
    return false;
}
