#include <stdio.h>
#include <stdint.h>
#include "sharedData.h"
#include "taskhandler.h"
#include "math.h"  // Include this for external math functions
#include "Protection.h"
#include "measurement.h"
#include "VoltageCalculation.h"
#include"VoltageProtection.h"
#include "CurrentCalculation.h"
#include"CurrentProtection.h" 





MEASURED_t Measured;
PROTECTION_t Protection;

// Function to handle hall position and protection
void handle_hall(uint8_t hall) {
    // Update hall position
    Measured.hallPosition = hall;

    // Check hall protection and update protection status
    Protection.faults.hallInvalid = check_hall_protection(hall);
}

// Main loop or fast loop function
void fast_loop(void) {
    // Use adcvalue from shareddata.h
// /    Measured.current.raw = adcvalue;
//      Measured.voltage.raw = adcvalue;  // Assuming another ADC channel handles voltage

    // Calculate current and voltage
    Measured.Current.calculated = calculate_current(Measured.Current.raw);
    Measured.Voltage.calculated = calculate_voltage(Measured.Voltage.raw);

    // Store the filtered current and calculated current
//    Measured.Current.filtered = filtered_current;
//    Measured.Current.calculated = current;

    // Calculate RPM from throttle ADC value
//    rpm = calculate_rpm(adcvalue.raw, MAX_RPM);

    // Call overvoltage and undervoltage protection checks
    Protection.faults.overVolt = check_overvoltage(Measured.Voltage.calculated);
    Protection.faults.underVolt = check_undervoltage(Measured.Voltage.calculated);

    // Call the current protection check
    Protection.faults.overCurrent = check_overCurrent(Measured.Current.calculated);
//    Protection.faults.throttle = check_throttle(rpm);
}



// Slow loop function to check brake status and adjust RPM accordingly
void slow_loop(void) {
    // Check brake status
//    brake = get_brakestatus();
//    Measured.brakeRaw = S;

    // Adjust RPM based on brake status
//    brake = update_rpm_based_on_brake_status(brake);
    
}
