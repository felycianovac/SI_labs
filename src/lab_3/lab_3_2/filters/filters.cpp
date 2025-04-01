#include "filters.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>  // for memset

#define MIN_VALID 0
#define MAX_VALID 1023
#define MAX_DELTA 100
#define BUFFER_SIZE 8

// Per-axis state
typedef struct {
    uint16_t buffer[BUFFER_SIZE];
    uint8_t idx;
    bool initialized;
    uint16_t last_valid;
} AxisFilterState;

static AxisFilterState y_state;
static AxisFilterState x_state;


static AxisFilterState* get_state(char axis) {
    return (axis == 'x') ? &x_state : &y_state;
}

void filters_init(void) {
    memset(&x_state, 0, sizeof(AxisFilterState)); // Initialize x_state
    memset(&y_state, 0, sizeof(AxisFilterState)); // Initialize y_state
    x_state.last_valid = 512; // Initialize to a mid-range value
    y_state.last_valid = 512;

    for (int i = 0; i < BUFFER_SIZE; i++) {
        x_state.buffer[i] = 512;
        y_state.buffer[i] = 512;
    }
    x_state.initialized = true;
    y_state.initialized = true;
}

uint16_t filter_salt_and_pepper(uint16_t input, char axis) {
    AxisFilterState* state = get_state(axis); // Get the state for the specified axis

    if (!state->initialized) { // Check if the filter is initialized
        filters_init(); // Initialize if not
    }

    if (input < MIN_VALID || input > MAX_VALID) {
        return state->last_valid; //
    }

    int delta = abs((int)input - (int)state->last_valid); // Calculate the delta
    if (delta > MAX_DELTA) {
        // Smooth the jump
        input = state->last_valid + ((input > state->last_valid) ? 1 : -1) * (delta / 4);
    }

    state->last_valid = input; // Update the last valid value
    return input;
}

uint16_t moving_average(uint16_t input, char axis) {
    AxisFilterState* state = get_state(axis); // Get the state for the specified axis

    if (!state->initialized) {
        filters_init();
    }

    state->buffer[state->idx] = input; // Store the new input in the buffer
    state->idx = (state->idx + 1) % BUFFER_SIZE; // Update the index of the buffer

    uint32_t sum = 0;
    for (uint8_t i = 0; i < BUFFER_SIZE; i++) { //
        sum += state->buffer[i]; //add the values in the buffer
    }

    return (uint16_t)(sum / BUFFER_SIZE);
}
