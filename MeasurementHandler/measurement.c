#include <stdio.h>
#include <stdint.h>  // Include for uint32_t
#include "measurement.h"
#include "VoltageCalculation.h"
#include "CurrentCalculation.h"
#include "math.h"
#include "sharedData.h"
#include"initialconfig.h"

// const uint32_t R1 = 438.507;
// const uint32_t R2 = 10;
//float filtered_current = 0;  // Filtered current valu
//float current = 0.0;
//float voltage =0;
// Function to map ADC value to RPM with offset
//FIXED_VALS_t fixedvalue;
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
uint32_t calculate_throttle(uint32_t adc_value,uint32_t max_rpm) {
    
    // Calculate RPM
    return adc_to_rpm(adc_value,Fixedvalue.MAX_RPM, Fixedvalue.ADC_MAX_VALUE, Fixedvalue.THROTTLE_START_ADC);
}

// Function to calculate the input voltage based on ADC value
float calculate_voltage(uint32_t adc_value) {
    // Calculate the output voltage from ADC value
    float Vout = (adc_value * Fixedvalue.REFERENCE_VOLTAGE) / Fixedvalue.ADC_RESOLUTION;

    // Calculate the input voltage based on the voltage divider formula
    Fixedvalue.voltage = (Vout * (Fixedvalue.R1 + Fixedvalue.R2)) / Fixedvalue.R2;
    return Fixedvalue.voltage;
}


float calculate_current(uint32_t adc_value) {
    // Apply a simple low-pass filter to smooth out the current measurement
    float difference = adc_value - Fixedvalue.filtered_current;
    float filtered_increment = difference / (1 << Fixedvalue.FILTER_SHIFT);
    Fixedvalue.filtered_current += filtered_increment;

    // Calculate the actual current value in amperes
    Fixedvalue.current = ((Fixedvalue.filtered_current * Fixedvalue.REFERENCE_VOLTAGE) /( Fixedvalue.ADC_RESOLUTION* Fixedvalue.SHUNT_RESISTOR * Fixedvalue.GAIN));

    // Return current as an unsigned int, assuming it's appropriate for your needs
    return Fixedvalue.current;
}

float measure_temperature(uint32_t adc_value){
    Fixedvalue.temperature =((Fixedvalue.V25 - Fixedvalue.VSENSE* adc_value)/Fixedvalue.AVG_SLOPE + 25.0f);
    return Fixedvalue.temperature;
}
