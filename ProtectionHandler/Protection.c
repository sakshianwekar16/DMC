#include <stdio.h>
#include <stdint.h>  // Include for uint32_t
#include "Protection.h"
#include "ThrottleProtection.h"
#include "VoltageProtection.h"
#include "CurrentProtection.h"
#include "math.h"

// Function to check if the input number is between 1 and 6
uint32_t check_hall_protection(uint32_t num) {
    // Perform the check
    return (num >= 1 && num <= 6) ? 1 : 0; // Return 1 for pass, 0 for fail
}

uint32_t check_throttle(uint32_t throttle) {
    // Check if throttle is greater than 800
    return (throttle > 800) ? 1 : 0; // Return 1 if throttle exceeds protection limit, 0 otherwise
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

// Function to check for overvoltage
uint32_t check_overvoltage(uint32_t voltage) {
    return (voltage > OVER_VOLTAGE_THRESHOLD) ? 1 : 0; // Return 1 if overvoltage, 0 otherwise
}

// Function to check for undervoltage
uint32_t check_undervoltage(uint32_t voltage) {
    return (voltage < UNDER_VOLTAGE_THRESHOLD) ? 1 : 0; // Return 1 if undervoltage, 0 otherwise
}

// Constants for current measurement
#define SHUNT_RESISTOR 0.005      // Shunt resistor value in ohms
#define GAIN 8.5                  // Gain factor
#define CURRENT_THRESHOLD 20.0    // Maximum current value in amperes
#define FILTER_SHIFT 6            // Bit shift for filtering (equivalent to dividing by 64)

// Global variables for current measurement
uint32_t filtered_current = 0;  // Filtered current value
uint32_t current = 0.0;                // Actual current value

void setup_currentMeasurementValues(void) {
    // Setup function if needed for current measurement configuration
    // Placeholder for future use if specific calculations are required
}

uint32_t calculateCurrent(uint32_t adc_value) {
    // Apply a simple low-pass filter to smooth out the current measurement
    uint32_t difference = adc_value - filtered_current;
    uint32_t filtered_increment = difference / (1 << FILTER_SHIFT);
    filtered_current += filtered_increment;

    // Calculate the actual current value in amperes
    current = ((filtered_current * REFERENCE_VOLTAGE) / ADC_RESOLUTION) / (SHUNT_RESISTOR * GAIN);

    // Check if the current exceeds the maximum allowed value
    return (current > CURRENT_THRESHOLD) ? 0 : 1; // Return 0 for fail, 1 for pass
}
