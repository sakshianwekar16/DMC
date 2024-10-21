// voltage_monitor.h

#ifndef VOLTAGE_MONITOR_H
#define VOLTAGE_MONITOR_H


/**
 * @brief Calculates the input voltage based on the ADC value.
 *
 * This function uses the ADC value and the reference voltage to compute the output voltage
 * from the ADC. Then, it calculates the input voltage using the voltage divider formula.
 *
 * @param adc_value The ADC value to convert.
 * @return The calculated input voltage.
 */
 uint32_t calculate_voltage(uint32_t adc_value);

/**
 * @brief Checks if the input voltage is above the overvoltage threshold.
 *
 * This function compares the provided voltage against the overvoltage threshold.
 *
 * @param voltage The voltage to check.
 * @return 1 if the voltage is above the overvoltage threshold, 0 otherwise.
 */
uint32_t check_overvoltage(uint32_t voltage);

/**
 * @brief Checks if the input voltage is below the undervoltage threshold.
 *
 * This function compares the provided voltage against the undervoltage threshold.
 *
 * @param voltage The voltage to check.
 * @return 1 if the voltage is below the undervoltage threshold, 0 otherwise.
 */
uint32_t check_undervoltage(uint32_t voltage);

#endif // VOLTAGE_MONITOR_H
