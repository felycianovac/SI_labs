#include "display.h"
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"
#include "../../../lab_1/led/led.h"


void display_update(SensorData data) {
    char buffer[10];  // Buffer to store distance value
    unsigned long timestamp = millis();  // Get current timestamp

    printf("\n============================================\r\n");
    printf("|  SENSOR REPORT                          |\r\n");
    printf("============================================\r\n");
    printf("| Timestamp: %lu ms                        |\r\n", timestamp);
    
    if (data.is_valid) { // Check if the data is valid
        dtostrf(data.distance_cm, 6, 2, buffer);  // Convert float to string


        printf("| Distance Measured: %s cm            |\r\n", buffer);   

        if (data.distance_cm < 10.0) { // Check if the distance is less than 10 cm
            printf("| ALERT: Object too close!                |\r\n");
            printf("| Sensor Status: CRITICAL                 |\r\n");
            ledOn(12);  // Turn on LED
        } 
        else if (data.distance_cm > 300.0) { // Check if the distance is greater than 300 cm
            printf("| ALERT: Object too far / Out of range!   |\r\n");
            printf("| Sensor Status: WARNING                  |\r\n");
            ledOn(12);  // Turn on LED
        } 
        else {
            printf("| Sensor Status: OK                       |\r\n");
            ledOff(12);  // Turn off LED
        }
    } else {
        printf("| ERROR: Out of range / Invalid Reading   |\r\n"); // Display error message
        printf("| Sensor Status: ERROR                    |\r\n");
        ledOn(12);  // Turn on LED
    }

    printf("============================================\r\n\n");
}