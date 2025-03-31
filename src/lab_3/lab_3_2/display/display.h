#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint16_t raw_x;
    uint16_t raw_y;
    float distance_raw;
    uint16_t filtered_x;
    uint16_t filtered_y;
    float distance_filtered;
    float voltage_x;
    float voltage_y;
    float percent_x;
    float percent_y;
    float distance_percent;
    bool button_state;
    unsigned long timestamp;
} DisplayData;

void display_init();
void display_full_status(const DisplayData* data);

#endif
