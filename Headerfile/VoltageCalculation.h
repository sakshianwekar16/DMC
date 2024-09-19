// voltage_calculation.h

#ifndef VOLTAGE_CALCULATION_H
#define VOLTAGE_CALCULATION_H

// Constants for voltage calculation
#define ADC_RESOLUTION 4096          // ADC resolution (e.g., 12-bit ADC)
#define REFERENCE_VOLTAGE 3.3        // Reference voltage for ADC
#define OVER_VOLTAGE_THRESHOLD 48.0  // Threshold for overvoltage in volts
#define UNDER_VOLTAGE_THRESHOLD 28.0 // Threshold for undervoltage in volts

// Voltage divider resistances
extern const uint32_t R1; // Resistance of R1 in ohms
extern const uint32_t R2; // Resistance of R2 in ohms

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
