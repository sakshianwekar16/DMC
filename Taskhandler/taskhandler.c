#include <stdio.h>
#include <stdint.h>
#include "taskhandler.h"
#include "math.h"  // Include this for the external function prototypes

// External variables
 uint32_t filtered_current =0;
 uint32_t current=0;
 uint32_t voltage=0;
 uint32_t rpm=0;
 uint32_t hall_position=0;
 uint32_t brake=0;
 
// Constants
#define ADC_RESOLUTION 4096
#define REFERENCE_VOLTAGE 3.3
#define OVER_VOLTAGE_THRESHOLD 48.0
#define UNDER_VOLTAGE_THRESHOLD 28.0
#define SHUNT_RESISTOR 0.005
#define GAIN 8.5
#define CURRENT_THRESHOLD 20.0
#define FILTER_SHIFT 6
#define ADC_MAX_VALUE 4096
#define THROTTLE_START_ADC 1000
#define MAX_RPM 1300

// Function to initialize or reset current measurement values
void setup_currentMeasurementValues(void) {
    // Initialization logic if needed
}

// Function to calculate current based on ADC value
uint32_t calculateCurrent(uint32_t adc_value) {
    // Apply a simple low-pass filter to smooth out the current measurement
    uint32_t difference = adc_value - filtered_current;
    uint32_t filtered_increment = difference / (1 << FILTER_SHIFT);
    filtered_current += filtered_increment;

    // Calculate the actual current value in amperes
    return ((filtered_current * REFERENCE_VOLTAGE) / ADC_RESOLUTION) / (SHUNT_RESISTOR * GAIN);
}

// Function to check current protection based on calculated current
uint32_t currentProtection(uint32_t current) {
    // Check if the current exceeds the maximum allowed value
    return (current >= CURRENT_THRESHOLD) ? 1 : 0; // Return 1 if current exceeds or equals threshold, 0 otherwise
}

// Function to calculate voltage based on ADC value
uint32_t calculate_voltage(uint32_t adc_value) {
    // Calculate the output voltage from ADC value
    uint32_t Vout = (adc_value * REFERENCE_VOLTAGE) / ADC_RESOLUTION;

    // Calculate the input voltage based on the voltage divider formula
    const uint32_t R1 = 438.507;
    const uint32_t R2 = 10;
    return(Vout * (R1 + R2)) / R2;
}

// Function to check if voltage exceeds overvoltage threshold
uint32_t check_overvoltage(uint32_t voltage) {
    return (voltage > OVER_VOLTAGE_THRESHOLD) ? 1 : 0; // Return 1 if overvoltage, 0 otherwise
}

// Function to check if voltage falls below undervoltage threshold
uint32_t check_undervoltage(uint32_t voltage) {
    return (voltage < UNDER_VOLTAGE_THRESHOLD) ? 1 : 0; // Return 1 if undervoltage, 0 otherwise
}



// Function to convert ADC value to RPM
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
uint32_t calculate_rpm(uint32_t adc_value, uint32_t max_rpm) {
    // Calculate RPM
    return adc_to_rpm(adc_value, max_rpm, ADC_MAX_VALUE, THROTTLE_START_ADC);
}

// Function to read ADC value, simulate ADC buffer input


// Function to check hall protection based on hall position
uint32_t check_hall_protection(uint32_t num) {
    // Perform the check
    return (num >= 1 && num <= 6) ? 1 : 0; // Return 1 if within range, 0 otherwise
}

uint32_t check_throttle(uint32_t rpm) {
    // Check if throttle is greater than 800
    return (rpm > 800) ? 1 : 0; // Return 1 if throttle exceeds protection limit, 0 otherwise
}

// Function to handle hall position and protection
void handle_hall(void) {
    // Get hall position
    hall_position = get_hall_position();
    

    // Check hall protection
    check_hall_protection(hall_position);

    // Perform actions based on hall protection check

}

// Function to get hall position


// Main loop or fast loop function
void fast_loop(void) {
    // Read ADC value
    uint32_t adc_value = read_adc_value();
    
    // Calculate current
    current = calculateCurrent(adc_value);
    
    // Check current protection
  

    // Calculate voltage
    voltage = calculate_voltage(adc_value);
    
    // Check voltage protection
    


    // Calculate RPM
    rpm = calculate_rpm(adc_value, MAX_RPM);
    
    // Handle hall protection


    // Implement additional logic if needed
}
 void update_rpm_based_on_brake_status(uint32_t brake) {
    if (brake == 1) {
        // Brake is engaged, set throttle RPM to 0
        rpm = 0;
    } else {
        // Brake is not engaged, set throttle RPM to calculated RPM
        uint32_t adc_value = read_adc_value();
        rpm = calculate_rpm(adc_value, MAX_RPM);
    }
 }
// Slow loop function to check brake status and adjust RPM accordingly
void slow_loop(void) {
    // Check brake status
    brake = get_brakestatus();
    update_rpm_based_on_brake_status(brake);
}


    // Additional processing based on brake status and RPM can be added here
