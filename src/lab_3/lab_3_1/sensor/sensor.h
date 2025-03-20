#ifndef SENSOR_H
#define SENSOR_H

#define TRIGGER_PIN 8
#define ECHO_PIN 7
#include <Arduino.h>

typedef struct {
    float distance_cm;
    bool is_valid;
} SensorData;

void sensor_setup();
SensorData sensor_read();

#endif
