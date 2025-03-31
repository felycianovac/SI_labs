#include "sensor.h"
#include "../taskmanager/taskmanager.h"

SensorData sensorData;

void sensor_setup() {
    pinMode(TRIGGER_PIN, OUTPUT); // Sets the TRIGGER_PIN as an Output
    pinMode(ECHO_PIN, INPUT); // Sets the ECHO_PIN as an Input
    
    // Debug: Check pin states
    printf("Ultrasonic sensor setup:\n");
    printf("TRIG pin (%d): %d\n", TRIGGER_PIN, digitalRead(TRIGGER_PIN));
    printf("ECHO pin (%d): %d\n", ECHO_PIN, digitalRead(ECHO_PIN));
}

SensorData sensor_read() {
    long duration; // Variable to store the duration of sound wave travel
    float distance; // Variable to store the distance value
    SensorData sensorData; // Variable to store the sensor data

    digitalWrite(TRIGGER_PIN, LOW); // Clears the TRIGGER_PIN
    delayMicroseconds(2); // Waits for 2 microseconds
    digitalWrite(TRIGGER_PIN, HIGH); // Sets the TRIGGER_PIN
    delayMicroseconds(10); // Waits for 10 microseconds
    digitalWrite(TRIGGER_PIN, LOW); // Clears the TRIGGER_PIN
    duration = pulseIn(ECHO_PIN, HIGH); // Reads the ECHO_PIN and stores the duration value
    distance = (duration * 0.034) / 2;  // Calculates the distance value
    
    // Debug: Print raw readings
    printf("Ultrasonic reading - Duration: %ld, Distance: %.2f cm\n", duration, distance);
    
    sensorData.distance_cm = distance; // Stores the distance value in the sensorData struct
    sensorData.is_valid = (distance > 2 && distance < 400); // Checks if the distance value is valid

    return sensorData;
}


