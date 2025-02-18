#include "lab_1_1_app.h"
#include "service_serial_stdio/service_serial_stdio.h"
#include <Arduino.h>
#include <string.h>

#define LED_PIN 13  

char commandBuffer[20];  // Buffer to store user input
int bufferIndex = 0;     // Keeps track of received characters

void lab_1_1_app_setup() {
    service_serial_stdio_setup();
    // pinMode(LED_PIN, OUTPUT);  // Set LED pin as output
    printf("MCU Ready. Send 'led on' or 'led off'.\n");
}

void lab_1_1_app_loop() {
        char command[20];
        int index = 0;
        
        while (Serial.available() > 0) {
            char c = getchar();
            if (c == '\r' || c == '\n') {  // Detect end of command
                if (index > 0) {
                    command[index] = '\0';
                    index = 0;
                    
                    printf("Comanda primita: %s\n", command);
                    
                    if (strcmp(command, "led on") == 0) {
                        printf("LED aprins!\n");
                    } else if (strcmp(command, "led off") == 0) {
                        printf("LED stins!\n");
                    } else {
                        printf("Comanda invalida! Utilizati 'led on' sau 'led off'.\n");
                    }
                }
            } else if (index < sizeof(command) - 1) {
                command[index++] = c;
            }
        }
    }