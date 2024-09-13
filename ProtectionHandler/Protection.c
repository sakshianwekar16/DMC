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
#define REFERENCE_VOLTAGE 3.3
#define OVER_VOLTAGE_THRESHOLD 48.0
#define UNDER_VOLTAGE_THRESHOLD 28.0

// Voltage divider resistances
const double R1 = 438.507;
const double R2 = 10;

// Function to calculate the input voltage based on ADC value
double calculate_voltage(unsigned int adc_value) {
    // Calculate the output voltage from ADC value
    double Vout = (adc_value * REFERENCE_VOLTAGE) / ADC_RESOLUTION;

    // Calculate the input voltage based on the voltage divider formula
    return (Vout * (R1 + R2)) / R2;
}

// Function to check for overvoltage
int check_overvoltage(double voltage) {
    return (voltage > OVER_VOLTAGE_THRESHOLD) ? 1 : 0; // Return 1 if overvoltage, 0 otherwise
}

// Function to check for undervoltage
int check_undervoltage(double voltage) {
    return (voltage < UNDER_VOLTAGE_THRESHOLD) ? 1 : 0; // Return 1 if undervoltage, 0 otherwise
}

//current Protection in CI/CD
// Constants
#define ADC_RESOLUTION 4095       // 12-bit ADC resolution
#define REFERENCE_VOLTAGE 3.3     // Reference voltage in volts
#define SHUNT_RESISTOR 0.005      // Shunt resistor value in ohms
#define GAIN 8.5                  // Gain factor
#define CURRENT_THRESHOLD 20.0    // Maximum current value in amperes
#define FILTER_SHIFT 6            // Bit shift for filtering (equivalent to dividing by 64)

// Global variables for current measurement
static double filtered_current = 0;  // Filtered current value
double current = 0.0;               // Actual current value

void setup_currentMeasurementValues(void) {
    // Setup function if needed for current measurement configuration
    // Placeholder for future use if specific calculations are required
}

int calculateCurrent(unsigned int adc_value) {
    // Apply a simple low-pass filter to smooth out the current measurement
    double difference = adc_value - filtered_current;
    double filtered_increment = difference / (1 << FILTER_SHIFT);
    filtered_current += filtered_increment;

    // Calculate the actual current value in amperes
    current = ((filtered_current * REFERENCE_VOLTAGE) / ADC_RESOLUTION) / (SHUNT_RESISTOR * GAIN);

    // Check if the current exceeds the maximum allowed value
    if (current > CURRENT_THRESHOLD) {
        return 0; // Fail
    } else {
        return 1; // Pass
    }
}
