// brake.h

#ifndef BRAKE_H
#define BRAKE_H

// Function declarations

/**
 * @brief Converts ADC value to RPM based on specified parameters.
 *
 * This function maps the ADC value to an RPM value using the provided parameters.
 *
 * @param adc_value The ADC value to convert.
 * @param max_rpm The maximum RPM corresponding to the maximum ADC value.
 * @param adc_max_value The maximum value of the ADC.
 * @param throttle_start_adc The ADC value where throttle starts.
 * @return The calculated RPM value.
 */
int adc_to_rpm(int adc_value, int max_rpm, int adc_max_value, int throttle_start_adc);

/**
 * @brief Calculates RPM based on ADC value.
 *
 * This function calculates the RPM from an ADC value using predefined maximum ADC value
 * and throttle start value.
 *
 * @param adc_value The ADC value to convert.
 * @param max_rpm The maximum RPM corresponding to the maximum ADC value.
 * @return The calculated RPM value.
 */
int calculate_rpm(int adc_value, int max_rpm);

/**
 * @brief Reads ADC value from a simulated ADC buffer.
 *
 * This function simulates reading an ADC value. Replace with actual ADC read code.
 *
 * @return The simulated ADC value.
 */
int read_adc_value(void);

/**
 * @brief Updates the throttle value based on brake status.
 *
 * This function updates the throttle value based on whether the brake is applied or not.
 * If the brake is applied, the throttle is set to 0. Otherwise, it is set based on RPM calculation.
 *
 * @param brake Indicates if the brake is applied (1) or not (0).
 * @param throttle Pointer to the throttle value to update.
 * @param max_rpm The maximum RPM for the calculation.
 */
void update_throttle(int brake, int *throttle, int max_rpm);

#endif // BRAKE_H
