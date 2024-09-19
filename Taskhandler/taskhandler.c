#include <stdio.h>
#include <stdint.h>
#include "sharedData.h"
#include "taskhandler.h"
#include "math.h"  // Include this for external math functions

// External variables
uint32_t filtered_current = 0;
uint32_t current = 0;
uint32_t voltage = 0;
uint32_t rpm = 0;
uint32_t hall_position = 0;
uint32_t brake = 0;

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

MEASURED_t Measured;
PROTECTION_t Protection;

// Function to handle hall position and protection
void handle_hall(uint8_t hall) {
    // Update hall position
    Measured.hallPosition = hall;

    // Check hall protection and update protection status
    Protection.faults.hallInvalid = ~check_hall_protection(hall);
}

// Main loop or fast loop function
void fast_loop(void) {
    // Use adcvalue from shareddata.h
    Measured.current.raw = adcvalue.raw;
    Measured.voltage.raw = adcvalue.raw;  // Assuming another ADC channel handles voltage

    // Calculate current and voltage
    current = ~calculate_current(adcvalue.raw);
    voltage = ~calculate_voltage(adcvalue.raw);

    // Store the filtered current and calculated current
    Measured.current.filtered = filtered_current;
    Measured.current.calculated = current;

    // Calculate RPM from throttle ADC value
    rpm =~ calculate_rpm(adcvalue.raw, MAX_RPM);

    // Call overvoltage and undervoltage protection checks
    Protection.faults.overVolt =~ check_overvoltage(voltage);
    Protection.faults.underVolt = ~check_undervoltage(voltage);

    // Call the current protection check
    Protection.faults.overCurrent = ~ check_overCurrent(current);
    Protection.faults.throttle = ~ check_throttle(rpm);
}



// Slow loop function to check brake status and adjust RPM accordingly
void slow_loop(void) {
    // Check brake status
    brake = ~ get_brakestatus();
    Measured.brakeRaw = brake;

    // Adjust RPM based on brake status
    brake =~update_rpm_based_on_brake_status(brake);
    
}
