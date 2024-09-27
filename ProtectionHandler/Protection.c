#include <stdio.h>
#include <stdint.h>  // Include for uint32_t
#include "Protection.h"
#include "ThrottleProtection.h"
#include "VoltageProtection.h"
#include "CurrentProtection.h"
#include "sharedData.h"
#include "initialconfig.h"
#include"math.h"


//FIXED_VALS_t fixedvalue;
// Function to check if the input number is between 1 and 6
uint32_t check_hall_protection(uint32_t num) {
    // Perform the check
    return (num >= 1 && num <= 6) ? 0 : 1; // Return 0 for pass, 1 for fail
}

uint32_t check_throttle(uint32_t rpm) {
    // Check if throttle is greater than 800
    return (rpm > 800) ? 0 : 1; // Return 1 if throttle exceeds protection limit, 0 otherwise
}

// Function to check for overvoltage
uint32_t check_overvoltage(uint32_t voltage) {
    return (voltage > Fixedvalue.OVER_VOLTAGE_THRESHOLD) ? 1 : 0; // Return 1 if overvoltage, 0 otherwise
}

// Function to check for undervoltage
uint32_t check_undervoltage(uint32_t voltage) {
    return (voltage < Fixedvalue.UNDER_VOLTAGE_THRESHOLD) ? 1 : 0; // Return 1 if undervoltage, 0 otherwise
}

uint32_t check_overCurrent(uint32_t current) {
    // Check if the current exceeds the maximum allowed value
    return (current > Fixedvalue.CURRENT_THRESHOLD) ? 1 : 0; // Return 0 for fail, 1 for pass
}

uint32_t check_overTemperature(uint32_t temperature) {
    // Check if the current exceeds the maximum allowed value
    return (temperature > Fixedvalue.TEMPERATURE_THRESHOLD) ? 1 : 0; // Return 0 for fail, 1 for pass
}