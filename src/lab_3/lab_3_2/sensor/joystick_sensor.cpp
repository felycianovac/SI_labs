#include "joystick_sensor.h"
#include <Arduino.h>

// Variabile pentru calibrare
static int16_t x_offset = 0;
static int16_t y_offset = 0;
static bool is_calibrated = false;

void sensor_init() {
    pinMode(JOYSTICK_X_PIN, INPUT);
    pinMode(JOYSTICK_Y_PIN, INPUT);
    pinMode(JOYSTICK_BTN_PIN, INPUT_PULLUP);

    delay(10);

    sensor_calibrate();
}

bool sensor_self_test() {
    uint16_t x = analogRead(JOYSTICK_X_PIN);
    uint16_t y = analogRead(JOYSTICK_Y_PIN);
    bool btn = digitalRead(JOYSTICK_BTN_PIN);

    return (x < 1024 && y < 1024);
}

void sensor_calibrate() {
    uint32_t sum_x = 0;
    uint32_t sum_y = 0;
    const uint8_t samples = 16;

    for(uint8_t i = 0; i < samples; i++) {
        sum_x += analogRead(JOYSTICK_X_PIN);
        sum_y += analogRead(JOYSTICK_Y_PIN);
        delay(10);
    }

    x_offset = (sum_x / samples) - JOYSTICK_CENTER_X;
    y_offset = (sum_y / samples) - JOYSTICK_CENTER_Y;
    
    is_calibrated = true;
}

bool is_reading_valid(uint16_t reading) {
    return (reading < 1024);
}

uint16_t read_joystick_x() {
    uint16_t raw_value = analogRead(JOYSTICK_X_PIN);
    if (!is_reading_valid(raw_value)) {
        return JOYSTICK_CENTER_X;
    }
    
    if (is_calibrated) {
        int16_t corrected = raw_value - x_offset;
        if (abs(corrected - JOYSTICK_CENTER_X) < JOYSTICK_DEADZONE) {
            return JOYSTICK_CENTER_X;
        }
        return constrain(corrected, 0, 1023);
    }
    
    return raw_value;
}

uint16_t read_joystick_y() {
    uint16_t raw_value = analogRead(JOYSTICK_Y_PIN);
    if (!is_reading_valid(raw_value)) {
        return JOYSTICK_CENTER_Y;
    }
    
    if (is_calibrated) {
        int16_t corrected = raw_value - y_offset;
        if (abs(corrected - JOYSTICK_CENTER_Y) < JOYSTICK_DEADZONE) {
            return JOYSTICK_CENTER_Y;
        }
        return constrain(corrected, 0, 1023);
    }
    
    return raw_value;
}

bool read_joystick_button() {
    bool state = true;
    for(uint8_t i = 0; i < 4; i++) {
        state &= (digitalRead(JOYSTICK_BTN_PIN) == LOW);
        delayMicroseconds(50);
    }
    return state;
}

SensorRawData read_sensor() {
    SensorRawData data;
    
    data.x_raw = read_joystick_x();
    data.y_raw = read_joystick_y();
    data.button_state = read_joystick_button();
    data.timestamp = millis();
    
    return data;
}
