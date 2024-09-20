#include <stdio.h>
#include <stdint.h>  // Include for uint32_t
#include "measurement.h"
#include "VoltageCalculation.h"
#include "CurrentCalculation.h"
#include "math.h"

// Function to map ADC value to RPM with offset
uint32_t adc_to_rpm(uint32_t adc_value, uint32_t max_rpm, uint32_t adc_max_value, uint32_t throttle_start_adc) {
    // Ensure the ADC value is within valid range
    if (adc_value < throttle_start_adc) {
        adc_value = throttle_start_adc; // If ADC value is below the throttle start, use the throttle start value
    } else if (adc_value > adc_max_value) {
        adc_value = adc_max_value;
    }

    // Calculate the effective ADC range above throttle start
    uint32_t effective_adc_range = adc_max_value - throttle_start_adc;
    uint32_t effective_adc_value = adc_value - throttle_start_adc;

    // Calculate RPM
    return (effective_adc_value * max_rpm) / effective_adc_range;
}

// Function to calculate RPM based on ADC value
uint32_t calculate_throttle(uint32_t adc_value, uint32_t max_rpm) {
    const uint32_t ADC_MAX_VALUE = 4096; // Maximum ADC value for 12-bit ADC
    const uint32_t THROTTLE_START_ADC = 1000; // ADC value where throttle starts
    
    // Calculate RPM
    return adc_to_rpm(adc_value, max_rpm, ADC_MAX_VALUE, THROTTLE_START_ADC);
}


#define ADC_RESOLUTION 4096
#define REFERENCE_VOLTAGE 3.3
#define OVER_VOLTAGE_THRESHOLD 48.0
#define UNDER_VOLTAGE_THRESHOLD 28.0

// Voltage divider resistances
const uint32_t R1 = 438.507;
const uint32_t R2 = 10;

// Function to calculate the input voltage based on ADC value
uint32_t calculate_voltage(uint32_t adc_value) {
    // Calculate the output voltage from ADC value
    uint32_t Vout = (adc_value * REFERENCE_VOLTAGE) / ADC_RESOLUTION;

    // Calculate the input voltage based on the voltage divider formula
    return (Vout * (R1 + R2)) / R2;
}

#define SHUNT_RESISTOR 0.005      // Shunt resistor value in ohms
#define GAIN 8.5                  // Gain factor
#define CURRENT_THRESHOLD 20.0    // Maximum current value in amperes
#define FILTER_SHIFT 6            // Bit shift for filtering (equivalent to dividing by 64)

// Global variables for current measurement
uint32_t filtered_current = 0;  // Filtered current value
uint32_t current = 0.0;         // Actual current value

void setup_currentMeasurementValues(void) {
    // Setup function if needed for current measurement configuration
    // Placeholder for future use if specific calculations are required
}

uint32_t calculate_current(uint32_t adc_value) {
    // Apply a simple low-pass filter to smooth out the current measurement
    uint32_t difference = adc_value - filtered_current;
    uint32_t filtered_increment = difference / (1 << FILTER_SHIFT);
    filtered_current += filtered_increment;

    // Calculate the actual current value in amperes
    current = ((filtered_current * REFERENCE_VOLTAGE) / ADC_RESOLUTION) / (SHUNT_RESISTOR * GAIN);

    // Return current as an unsigned int, assuming it's appropriate for your needs
    return (uint32_t)current;
}
