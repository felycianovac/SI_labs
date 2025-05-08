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
    tachPin = pin;
    pinMode(tachPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(tachPin), tachISR, FALLING);
    lastCheck = millis();
    
    // Initialize filter
    for (int i = 0; i < RPM_FILTER_SIZE; i++) {
        rpmHistory[i] = 0;
    }
}

int Tachometer_GetRPM() {
    unsigned long currentTime = millis();
    unsigned long timeElapsed = currentTime - lastCheck;
    
    // Update RPM calculation every 500ms
    if (timeElapsed >= 500) {
        noInterrupts();
        unsigned int count = pulseCount;
        pulseCount = 0;
        interrupts();
        
        // Most CPU fans send 2 pulses per revolution
        // RPM = (pulses / 2 pulses per rev) * (60 sec / measured_time_in_sec)
        int newRpm = (count * 120) / (timeElapsed / 1000.0);
        
        // Filter out implausible readings
        if (newRpm > 10000) {
            // Likely a glitch, ignore this reading
            newRpm = rpm; // Keep previous value
        }
        
        // Add to moving average filter
        rpmHistory[rpmHistoryIndex] = newRpm;
        rpmHistoryIndex = (rpmHistoryIndex + 1) % RPM_FILTER_SIZE;
        
        // Calculate filtered RPM (moving average)
        int sum = 0;
        int validCount = 0;
        for (int i = 0; i < RPM_FILTER_SIZE; i++) {
            if (rpmHistory[i] > 0) {
                sum += rpmHistory[i];
                validCount++;
            }
        }
        
        if (validCount > 0) {
            rpm = sum / validCount;
        } else {
            rpm = newRpm;
        }
        
        lastCheck = currentTime;
    }
    
    return rpm;
}