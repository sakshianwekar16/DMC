// voltage_calculation.h
#include<stdint.h>
#ifndef VOLTAGE_CALCULATION_H
#define VOLTAGE_CALCULATION_H

// Constants for voltage calculation
// Resistance of R2 in ohms
// extern float voltage;
/**
 * @brief Calculates the input voltage based on the ADC value.
 *
 * This function computes the input voltage using the ADC value and the reference voltage.
 * It assumes a voltage divider configuration for measurement, where the resistances of R1
 * and R2 are used to scale the input voltage down to the ADC's measurable range.
 *
 * @param adc_value The ADC value to convert to voltage.
 * @return The calculated input voltage.
 */
uint32_t calculate_voltage(uint32_t adc_value);

#endif // VOLTAGE_CALCULATION_H
