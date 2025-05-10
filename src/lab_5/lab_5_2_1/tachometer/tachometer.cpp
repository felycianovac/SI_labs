#include "tachometer.h"
#include <Arduino.h>

// Variables for tachometer readings
static volatile unsigned int pulseCount = 0;
static unsigned long lastCheck = 0;
static int rpm = 0;
static int tachPin = 2;

// Moving average filter variables for stabilizing RPM readings
#define RPM_FILTER_SIZE 5
static int rpmHistory[RPM_FILTER_SIZE] = {0};
static int rpmHistoryIndex = 0;

void tachISR() {
    pulseCount++;
}

void Tachometer_Init(int pin) {
    tachPin = pin; // Set the tachometer pin
    pinMode(tachPin, INPUT_PULLUP); // Set pin as input with pull-up resistor
    attachInterrupt(digitalPinToInterrupt(tachPin), tachISR, FALLING); // Attach interrupt on falling edge
    lastCheck = millis(); // Initialize last check time
    
    // Initialize filter
    for (int i = 0; i < RPM_FILTER_SIZE; i++) {
        rpmHistory[i] = 0; // Initialize filter history to zero
    }
}

int Tachometer_GetRPM() {
    unsigned long currentTime = millis(); // Get current time
    unsigned long timeElapsed = currentTime - lastCheck; // Calculate elapsed time since last check
    
    // Update RPM calculation every 500ms
    if (timeElapsed >= 500) {
        noInterrupts(); // Disable interrupts to safely read pulseCount
        unsigned int count = pulseCount; // Store pulse count
        pulseCount = 0; // Reset pulse count for next interval
        interrupts(); // Re-enable interrupts
        
        // Most CPU fans send 2 pulses per revolution
        // RPM = (pulses / 2 pulses per rev) * (60 sec / measured_time_in_sec)
        int newRpm = (count * 30) / (timeElapsed / 1000.0); // Calculate RPM
         
        // Filter out implausible readings
        if (newRpm > 10000) {
            // Likely a glitch, ignore this reading
            newRpm = rpm; // Keep previous value
        }
        
        // Add to moving average filter
        rpmHistory[rpmHistoryIndex] = newRpm; // Store new RPM in history
        rpmHistoryIndex = (rpmHistoryIndex + 1) % RPM_FILTER_SIZE; // Set index for next entry
        
        // Calculate filtered RPM (moving average)
        int sum = 0; // Initialize sum for moving average
        int validCount = 0; // Initialize valid count for non-zero entries
        for (int i = 0; i < RPM_FILTER_SIZE; i++) {
            if (rpmHistory[i] > 0) { 
                sum += rpmHistory[i]; // Add to sum if valid
                validCount++;
            }
        }
        
        if (validCount > 0) {
            rpm = sum / validCount; // Calculate average RPM
        } else {
            rpm = newRpm;
        }
        
        lastCheck = currentTime; // Update last check time
    }
    
    return rpm;
}