#include <stdio.h>

// Function to check if the input number is between 1 and 6
int check_hall_protection(unsigned int num) {
    // Perform the check
    if (num >= 1 && num <= 6) {
        return 1; // Pass
    } else {
        return 0; // Fail
    }
}

int check_throttle(int throttle) {
    // Check if throttle is greater than 800
    if (throttle > 800) {
        return 1; // Throttle exceeds protection limit
    } else {
        return 0; // Throttle is within protection limit
    }
}
 

#define ADC_RESOLUTION 4096
#define REFERENCE_VOLTAGE 5.0
#define OVER_VOLTAGE_THRESHOLD 48.0
#define UNDER_VOLTAGE_THRESHOLD 28.0

// Function to calculate the voltage based on ADC value
double calculate_voltage(unsigned int adc_value) {
   
  return (adc_value * REFERENCE_VOLTAGE) / ADC_RESOLUTION;
}

// Function to check for overvoltage
int check_overvoltage(double voltage) {
    return (voltage > OVER_VOLTAGE_THRESHOLD) ? 1 : 0; // Return 1 if overvoltage, 0 otherwise
}

// Function to check for undervoltage
int check_undervoltage(double voltage) {
    return (voltage < UNDER_VOLTAGE_THRESHOLD) ? 1 : 0; // Return 1 if undervoltage, 0 otherwise
}
