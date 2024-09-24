// current_measurement.h
#include<stdint.h>
#ifndef CURRENT_MEASUREMENT_H
#define CURRENT_MEASUREMENT_H

            

/**
 * @brief Setup function for current measurement.
 *
 * This function is a placeholder for any future configuration required for
 * current measurement. Currently, it does not perform any actions.
 */
void setup_currentMeasurementValues(void);

/**
 * @brief Calculates the current based on ADC value and applies filtering.
 *
 * This function computes the actual current value using a low-pass filter to
 * smooth out the ADC measurements. It then updates the `current` variable
 * with the calculated value.
 *
 * @param adc_value The ADC value representing the current measurement.
 * @return 1 if the current is within the acceptable range, 0 otherwise (indicating a failure).
 */
float calculate_current(uint32_t adc_value);
#endif // CURRENT_MEASUREMENT_H
