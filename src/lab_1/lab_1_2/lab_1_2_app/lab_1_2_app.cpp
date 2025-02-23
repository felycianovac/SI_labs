#include "../../led/led.h"
#include "../lcd_stdio/lcd_stdio.h"
#include "../keypad_stdio/keypad_stdio.h"

void lab_1_2_app_setup() {
    Serial.begin(9600);
    
    // Initialize components
    ledSetup();
    lcdSetup();
    keypadSetup();
    
    // Set up stdio streams
    stdout = &lcd_stdout;
    stdin = &keypad_stdin;
    
    // Show initial prompt in the LCD
    printf("Enter Code:\n");
}

void lab_1_2_app_loop() {
    // Read code using scanf
    scanf("%4s", enteredCode);
    enteredCode[4] = '\0';
    
    // Check code and update outputs
    if (strcmp(enteredCode, correctCode) == 0) {
        // Access granted
        printf("\nAccess Granted");
        // Turn on green LED
        ledOn(GREEN_LED);
        ledOff(RED_LED);
    } else {
        // Access denied
        printf("\nAccess Denied");
        // Turn on red LED
        ledOff(GREEN_LED);
        ledOn(RED_LED);
    }
    
    // Wait and reset
    delay(2000);
    ledOff(GREEN_LED);
    ledOff(RED_LED);
    // Clear the entered code
    memset(enteredCode, 0, sizeof(enteredCode));
    printf("\nEnter Code:\n");
}