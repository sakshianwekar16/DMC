// voltage_monitor.h

#ifndef VOLTAGE_MONITOR_H
#define VOLTAGE_MONITOR_H

// Constants for ADC and voltage thresholds
#define ADC_RESOLUTION 4096            // ADC resolution (e.g., 12-bit ADC)
#define REFERENCE_VOLTAGE 3.3          // Reference voltage for ADC
#define OVER_VOLTAGE_THRESHOLD 48.0    // Threshold for overvoltage in volts
#define UNDER_VOLTAGE_THRESHOLD 28.0   // Threshold for undervoltage in volts

// Voltage divider resistances
extern const double R1; // Resistance of R1 in ohms
extern const double R2; // Resistance of R2 in ohms

/**
 * @brief Calculates the input voltage based on the ADC value.
 *
 * This function uses the ADC value and the reference voltage to compute the output voltage
 * from the ADC. Then, it calculates the input voltage using the voltage divider formula.
 *
 * @param adc_value The ADC value to convert.
 * @return The calculated input voltage.
 */
double calculate_voltage(unsigned int adc_value);

/**
 * @brief Checks if the input voltage is above the overvoltage threshold.
 *
 * This function compares the provided voltage against the overvoltage threshold.
 *
 * @param voltage The voltage to check.
 * @return 1 if the voltage is above the overvoltage threshold, 0 otherwise.
 */
int check_overvoltage(double voltage);

/**
 * @brief Checks if the input voltage is below the undervoltage threshold.
 *
 * This function compares the provided voltage against the undervoltage threshold.
 *
 * @param voltage The voltage to check.
 * @return 1 if the voltage is below the undervoltage threshold, 0 otherwise.
 */
int check_undervoltage(double voltage);

#endif // VOLTAGE_MONITOR_H
