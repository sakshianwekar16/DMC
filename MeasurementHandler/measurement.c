#include <stdio.h>
#include "measurement.h"
#include "VoltageCalculation.h"
#include "CurrentCalculation.h"

// Function to map ADC value to RPM with offset
unsigned int adc_to_rpm(unsigned int adc_value, int max_rpm, int adc_max_value, int throttle_start_adc) {
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
unsigned int calculate_rpm(unsigned int adc_value, unsigned int max_rpm) {
    const int ADC_MAX_VALUE = 4096; // Maximum ADC value for 12-bit ADC
    const int THROTTLE_START_ADC = 1000; // ADC value where throttle starts
    
    // Calculate RPM
    return adc_to_rpm(adc_value, max_rpm, ADC_MAX_VALUE, THROTTLE_START_ADC);
}

// Function to read ADC value, simulate ADC buffer input
unsigned int read_adc_value(void) {
    // Simulate reading from ADC buffer (replace this with actual ADC read)
    unsigned int adc_value = 1024; // Example value, replace with actual ADC read

    // Return ADC value
    return adc_value;
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



#define ADC_RESOLUTION 4096       // 12-bit ADC resolution
#define REFERENCE_VOLTAGE 3.3     // Reference voltage in volts
#define SHUNT_RESISTOR 0.005      // Shunt resistor value in ohms
#define GAIN 8.5                  // Gain factor
#define CURRENT_THRESHOLD 20.0    // Maximum current value in amperes
#define FILTER_SHIFT 6            // Bit shift for filtering (equivalent to dividing by 64)

// Global variables for current measurement
extern double filtered_current = 0;  // Filtered current value
extern double current = 0.0;         // Actual current value

void setup_currentMeasurementValues(void) {
    // Setup function if needed for current measurement configuration
    // Placeholder for future use if specific calculations are required
}

unsigned int calculateCurrent(unsigned int adc_value) {
    // Apply a simple low-pass filter to smooth out the current measurement
    double difference = adc_value - filtered_current;
    double filtered_increment = difference / (1 << FILTER_SHIFT);
    filtered_current += filtered_increment;

    // Calculate the actual current value in amperes
    current = ((filtered_current * REFERENCE_VOLTAGE) / ADC_RESOLUTION) / (SHUNT_RESISTOR * GAIN);

    // Return current as an unsigned int, assuming it's appropriate for your needs
    return (unsigned int)current;
}
