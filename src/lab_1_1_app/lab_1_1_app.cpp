#include "lab_1_1_app.h"
#include "led/led.h"
#include "service_serial_stdio/service_serial_stdio.h"
#include <Arduino.h>
#include <string.h>


void lab_1_1_app_setup() {
    ledSetup();
    service_serial_stdio_setup();
    printf("MCU Ready. Send 'led on!' or 'led off!'.\n");
}

void lab_1_1_app_loop() {
    //declare a char variable to store the received command
    char command[20];
    
    // Prompt user for input
    printf("\nEnter command: ");
    // ensure the prompt is displayed before reading input
    fflush(stdout);
    
    // Use scanf to read until exclamation mark
    if (scanf("%19[^!]%*c", command) == 1) {
        // Print the received command
        printf("\nReceived Command: %s\n", command);
        
        // Trim any whitespace
        char *trimmed = command;
        // Trim leading whitespace
        while (isspace(*trimmed)) trimmed++;
        
        // Check commands
        if (strcmp(trimmed, "led on") == 0) {
            // Turn on the LED
            ledOn();
            printf("LED turned on!\n");
        } else if (strcmp(trimmed, "led off") == 0) {
            // Turn off the LED
            ledOff();
            printf("LED turned off!\n");
        } else {
            // Invalid command
            printf("Invalid Command! Use 'led on' or 'led off'.\n");
        }
        
    } else {
        printf("Error reading command!\n");
    }
    // Clear the buffer
    while (Serial.available()) {
        Serial.read();
    }
    
    delay(100); // Small delay to prevent CPU overload
}