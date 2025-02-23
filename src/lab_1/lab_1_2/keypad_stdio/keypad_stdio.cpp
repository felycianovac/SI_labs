#include "keypad_stdio.h"

// Keypad configuration
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
// Keypad pins connected to the Arduino
byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = {9, 8, 7, 6};

// Create keypad instance
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
FILE keypad_stdin;

// Code validation
const char correctCode[] = "2354";
char enteredCode[5] = "";

void keypadSetup() {
    fdev_setup_stream(&keypad_stdin, NULL, keypad_getchar, _FDEV_SETUP_READ);
}

int keypad_getchar(FILE* stream) {
    // Wait for a key to be pressed
    char key;
    do {
        // Get the key
        key = keypad.getKey();
        // Small delay to prevent CPU overload
        delay(10);
    } while (!key);
    
    Serial.print(key);  // Echo to Serial Monitor
    fputc(key, &lcd_stdout);  // Echo to LCD
    return key;
}
