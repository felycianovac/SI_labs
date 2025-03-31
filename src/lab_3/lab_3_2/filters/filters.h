#ifndef FILTERS_H
#define FILTERS_H

#include <stdint.h>

void filters_init(void);

uint16_t filter_salt_and_pepper(uint16_t input, char axis);
uint16_t moving_average(uint16_t input, char axis);

#endif
