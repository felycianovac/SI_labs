#ifndef CONVERSION_H
#define CONVERSION_H

#include <stdint.h>

// Funcții de conversie ADC -> Voltage -> Physical Parameter
float adc_to_voltage(uint16_t adc_val);
float voltage_to_physical_parameter(float voltage);


// Funcții pentru saturație și calibrare
float apply_voltage_limits(float voltage);
float apply_parameter_limits(float parameter);

// Constante pentru calibrare (pot fi modificate după necesități)
#define ADC_RESOLUTION 1023.0f
#define VREF 5.0f
#define PARAM_MIN 0.0f
#define PARAM_MAX 100.0f

#endif
