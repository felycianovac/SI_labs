#include "display.h"
#include "../../../lab_1/lab_1_1/service_serial_stdio/service_serial_stdio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 16

static char str_time[MAX_STR_LEN];
static char str_raw_x[MAX_STR_LEN];
static char str_raw_y[MAX_STR_LEN];
static char str_filtered_x[MAX_STR_LEN];
static char str_filtered_y[MAX_STR_LEN];
static char str_voltage_x[MAX_STR_LEN];
static char str_voltage_y[MAX_STR_LEN];
static char str_percent_x[MAX_STR_LEN];
static char str_percent_y[MAX_STR_LEN];

static void uint16_to_str(uint16_t value, char* buffer) {
    snprintf(buffer, MAX_STR_LEN, "%4u", value);
}

static void float_to_voltage_str(float value, char* buffer) {
    dtostrf(value, 4, 2, buffer);
    strcat(buffer, " V");
}

static void float_to_percent_str(float value, char* buffer) {
    dtostrf(value, 4, 1, buffer);
    strcat(buffer, "%%");  
}

static void ulong_to_time_str(unsigned long value, char* buffer) {
    snprintf(buffer, MAX_STR_LEN, "%lu", value);
}

void display_init() {
    printf("\nJoystick Monitoring System\r\n");
    printf("=========================\r\n\n");
}

void display_full_status(const DisplayData* data) {
    ulong_to_time_str(data->timestamp, str_time);
    uint16_to_str(data->raw_x, str_raw_x);
    uint16_to_str(data->raw_y, str_raw_y);
    uint16_to_str(data->filtered_x, str_filtered_x);
    uint16_to_str(data->filtered_y, str_filtered_y);
    float_to_voltage_str(data->voltage_x, str_voltage_x);
    float_to_voltage_str(data->voltage_y, str_voltage_y);
    float_to_percent_str(data->percent_x, str_percent_x);
    float_to_percent_str(data->percent_y, str_percent_y);

    // Clear screen
    printf("\r\n");
    
    // Header
    printf("Joystick Status Report\r\n");
    printf("=====================\r\n\n");
    
    // Timestamp
    printf("Time: %s ms\r\n", str_time);
    printf("--------------------\r\n");
    
    // Raw values
    printf("Raw ADC Values:\r\n");
    printf("  X: %s\r\n", str_raw_x);
    printf("  Y: %s\r\n", str_raw_y);
    printf("--------------------\r\n");
    
    // Filtered values
    printf("Filtered Values:\r\n");
    printf("  X: %s\r\n", str_filtered_x);
    printf("  Y: %s\r\n", str_filtered_y);
    printf("--------------------\r\n");
    
    // Voltage values
    printf("Voltage:\r\n");
    printf("  X: %s\r\n", str_voltage_x);
    printf("  Y: %s\r\n", str_voltage_y);
    printf("--------------------\r\n");
    
    // Percentage values
    printf("Percentage:\r\n");
    printf("  X: %s\r\n", str_percent_x);
    printf("  Y: %s\r\n", str_percent_y);
    printf("--------------------\r\n");
    
    // Button state
    printf("Button State: %s\r\n", 
           data->button_state ? "PRESSED" : "RELEASED");
    printf("=====================\r\n\n");
}

