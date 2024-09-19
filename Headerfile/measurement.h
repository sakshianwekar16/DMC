// rpm_tests.h

#ifndef RPM_TESTS_H
#define RPM_TESTS_H
#include"stdint.h"
/**
 * @brief Runs RPM test cases and prints the results.
 *
 * This function defines several test cases with different ADC values and their expected
 * RPM results. It calls the calculate_rpm function to compute the RPM for each ADC value
 * and compares it with the expected result. It prints whether each test case passed or failed.
 */
void run_rpm_tests(void);
uint32_t adc_to_rpm(uint32_t adc_value, uint32_t max_rpm, uint32_t adc_max_value, uint32_t throttle_start_adc);
/**
 * @brief Calculates RPM based on ADC value and maximum RPM.
 *
 * This function calculates RPM from an ADC value using a predefined maximum ADC value
 * and throttle start value. It uses the adc_to_rpm function with these predefined parameters.
 *
 * @param adc_value The ADC value to convert.
 * @param max_rpm The maximum RPM value corresponding to the maximum ADC value.
 * @return The calculated RPM value.
 */
 uint32_t calculate_rpm(uint32_t adc_value, uint32_t max_rpm);

#endif // RPM_TESTS_H
