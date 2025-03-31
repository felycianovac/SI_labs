#include "conversion.h"

#define ADC_MIN 0
#define ADC_MAX 1023
#define VOLTAGE_MIN 0.0f
#define VOLTAGE_MAX 5.0f

#define VOLTAGE_OFFSET 0.0f
#define VOLTAGE_SCALE 20.0f  

float apply_voltage_limits(float voltage) {
    if (voltage < VOLTAGE_MIN) return VOLTAGE_MIN;
    if (voltage > VOLTAGE_MAX) return VOLTAGE_MAX;
    return voltage;
}

float apply_parameter_limits(float parameter) {
    if (parameter < PARAM_MIN) return PARAM_MIN;
    if (parameter > PARAM_MAX) return PARAM_MAX;
    return parameter;
}

float adc_to_voltage(uint16_t adc_val) {
    float voltage = ((float)adc_val / ADC_RESOLUTION) * VREF;
    return apply_voltage_limits(voltage);
}

float voltage_to_physical_parameter(float voltage) {
    float parameter = (voltage - VOLTAGE_OFFSET) * VOLTAGE_SCALE;
    
    return apply_parameter_limits(parameter);
}
