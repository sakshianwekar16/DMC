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

MEASURED_T Measured;
PROTECTION_t Protection;


// Function to handle hall position and protection
void handle_hall(uint8_t hall) {
    // Check hall protection
	Measured.hallPosition = hall;
    Protection.faults.hallInvalid = ~check_hall_protection(hall);
}

// Function to get hall position


// Main loop or fast loop function
void fast_loop(void) {
    current = calculate_current(adc_value);
    voltage = calculate_voltage(adc_value);
    
    
    // Calculate RPM
    rpm = calculate_rpm(adc_value, MAX_RPM);

}

// Slow loop function to check brake status and adjust RPM accordingly
void slow_loop(void) {
    // Check brake status
    brake = get_brakestatus();
    update_rpm_based_on_brake_status(brake);
}


