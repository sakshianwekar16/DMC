// brake.c
#include <stdio.h>
#include"sharedData.h" 
#include <stdint.h>
#include"sharedData.h"
#include"initialconfig.h"
//FIXED_VALS_t fixedvalue;


uint32_t convert_adc_to_rpm(adcvalue) {
    // Scale ADC value to RPM range
    return (adcvalue * Fixedvalue.MAX_RPM) / (Fixedvalue.ADC_MAX_VALUE - 1);  // Adjust if ADC_MAX_VALUE is not 4095
}
uint32_t rpm;
void update_rpm_based_on_brake_status(uint32_t brake_status) {
    if (brake_status > 0) {
        // If brake is applied, set RPM to minimum
        rpm = 0;
    } else {
        // If brake is not applied, convert ADC value to RPM
        rpm = convert_adc_to_rpm(adcvalue);
    }
}
//// Function prototypes
//unsigned int adc_to_rpm(unsigned int adc_value, unsigned int max_rpm, unsigned int adc_max_value, unsigned int throttle_start_adc);
//unsigned int calculate_rpm(unsigned int adc_value, unsigned int max_rpm);
//unsigned int read_adc_value(void);
//unsigned int update_throttle(unsigned int brake, int *throttle, unsigned int max_rpm);
//
//// Function to convert ADC value to RPM
//unsigned int adc_to_rpm(unsigned int adc_value,unsigned int max_rpm, unsigned int adc_max_value,unsigned int throttle_start_adc) {
//    // Ensure the ADC value is within the valid range
//    if (adc_value < throttle_start_adc) {
//        adc_value = throttle_start_adc; // Use the throttle start value if ADC is below the threshold
//    } else if (adc_value > adc_max_value) {
//        adc_value = adc_max_value; // Cap the ADC value at its maximum
//    }
//
//    // Calculate the effective ADC range above the throttle start
//    int effective_adc_range = adc_max_value - throttle_start_adc;
//    int effective_adc_value = adc_value - throttle_start_adc;
//
//    // Calculate RPM
//    return (effective_adc_value * max_rpm) / effective_adc_range;
//}
//
//// Function to calculate RPM based on ADC value
// unsigned int calculate_rpm(unsigned int adc_value, unsigned int max_rpm) {
//    const int ADC_MAX_VALUE = 4096; // Maximum ADC value for 12-bit ADC
//    const int THROTTLE_START_ADC = 1000; // ADC value where throttle starts
//
//    // Calculate RPM
//    return adc_to_rpm(adc_value, max_rpm, ADC_MAX_VALUE, THROTTLE_START_ADC);
//}
//
//// Function to simulate reading from an ADC
//unsigned int read_adc_value(void) {
//    // Simulate reading from ADC buffer (replace with actual ADC read)
//    return 1024; // Example value, replace with actual ADC read
//}
//
//// Function to update throttle based on brake status
//unsigned int update_throttle(unsigned int brake, int *throttle,unsigned int max_rpm) {
//    // Read the ADC value
//    int adc_value = read_adc_value();
//
//    if (brake == 1) {
//        // Set throttle to 0 if brake is applied
//        *throttle = 0;
//    } else {
//        // Calculate and set throttle to RPM value if brake is not applied
//        *throttle = calculate_rpm(adc_value, max_rpm);
//    }
//}
