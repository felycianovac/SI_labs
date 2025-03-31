#ifndef JOYSTICK_SENSOR_H
#define JOYSTICK_SENSOR_H

#include <stdint.h>
#include <stdbool.h>

// Structură pentru datele brute ale senzorului
typedef struct {
    uint16_t x_raw;
    uint16_t y_raw;
    bool button_state;
    uint32_t timestamp;
} SensorRawData;

// Configurație pin-uri
#define JOYSTICK_X_PIN A0     
#define JOYSTICK_Y_PIN A1     
#define JOYSTICK_BTN_PIN 2 

// Constante pentru calibrare
#define JOYSTICK_CENTER_X 512
#define JOYSTICK_CENTER_Y 512
#define JOYSTICK_DEADZONE 50

// Funcții pentru inițializare și citire
void sensor_init(void);
SensorRawData read_sensor(void);

// Funcții individuale pentru citire
uint16_t read_joystick_x(void);
uint16_t read_joystick_y(void);
bool read_joystick_button(void);

// Funcții pentru calibrare și verificare
bool sensor_self_test(void);
void sensor_calibrate(void);
bool is_reading_valid(uint16_t reading);

#endif
