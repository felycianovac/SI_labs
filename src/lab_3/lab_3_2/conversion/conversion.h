#ifndef CONVERSION_H
#define CONVERSION_H

#include <stdint.h>

float adc_to_voltage(uint16_t adc_val);
float adc_to_angle(uint16_t adc_val);  // ✅ nouă


float apply_voltage_limits(float voltage);
float apply_parameter_limits(float parameter);

#define ADC_RESOLUTION 1023.0f
#define VREF 5.0f
#define PARAM_MIN 0.0f
#define PARAM_MAX 100.0f

#endif
