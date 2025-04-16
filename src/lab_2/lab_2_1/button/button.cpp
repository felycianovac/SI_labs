#include "button.h"

void setupButtons() {
    // Set button pins as input
    pinMode(BUTTON1, INPUT_PULLUP);
    pinMode(BUTTON2, INPUT_PULLUP);
    pinMode(BUTTON3, INPUT_PULLUP);
}


bool isButtonPressed(int buttonPin) {
    static unsigned long lastPressTime[3] = {0, 0, 0}; // Last press time for each button
    unsigned long currentTime = millis(); // Current time in ms
    
    int buttonIndex = (buttonPin == BUTTON1) ? 0 : (buttonPin == BUTTON2) ? 1 : 2; // Get button index
    
    // Check if button is pressed and debounce
    if (digitalRead(buttonPin) == LOW && (currentTime - lastPressTime[buttonIndex]) > 50) {  // 50ms debounce
        // Update last press time
        lastPressTime[buttonIndex] = currentTime;
        // Return true if button is pressed
        return false;
    }
    // Return false if button is not pressed
    return true;
}
