#include <stdio.h>

// Function to map ADC value to RPM with offset
int adc_to_rpm(int adc_value, int max_rpm, int adc_max_value, int throttle_start_adc) {
    // Ensure the ADC value is within valid range
    if (adc_value < throttle_start_adc) {
        adc_value = throttle_start_adc; // If ADC value is below the throttle start, use the throttle start value
    } else if (adc_value > adc_max_value) {
        adc_value = adc_max_value;
    }

    // Calculate the effective ADC range above throttle start
    int effective_adc_range = adc_max_value - throttle_start_adc;
    int effective_adc_value = adc_value - throttle_start_adc;

    // Calculate RPM
    return (effective_adc_value * max_rpm) / effective_adc_range;
}

// Function to calculate RPM based on ADC value
int calculate_rpm(int adc_value, int max_rpm) {
    const int ADC_MAX_VALUE = 4096; // Maximum ADC value for 12-bit ADC
    const int THROTTLE_START_ADC = 1000; // ADC value where throttle starts
    
    // Calculate RPM
    return adc_to_rpm(adc_value, max_rpm, ADC_MAX_VALUE, THROTTLE_START_ADC);
}

// Function to read ADC value, simulate ADC buffer input
int read_adc_value(void) {
    // Simulate reading from ADC buffer (replace this with actual ADC read)
    int adc_value = 1024; // Example value, replace with actual ADC read

    // Return ADC value
    return adc_value;
}