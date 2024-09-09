// voltage_main.c
#include <stdio.h>
 // Include the header file where functions are declared
#include <stddef.h>  

#define ADC_RESOLUTION 4096
#define REFERENCE_VOLTAGE 5.0
#define OVER_VOLTAGE_THRESHOLD 48.0
#define UNDER_VOLTAGE_THRESHOLD 28.0     // Include to define size_t

int main() {
    // Test cases with ADC values
    unsigned int adc_values[] = {0, 512, 1024, 1500, 2000, 2048, 3000, 3072, 4096};
    size_t num_values = sizeof(adc_values) / sizeof(adc_values[0]);

    for (size_t i = 0; i < num_values; i++) {
        double voltage = calculate_voltage(adc_values[i]);

        // Print the calculated voltage for debugging
        printf("ADC Value: %u -> Calculated Voltage: %.2f V\n", adc_values[i], voltage);

        // Check voltage conditions
        if (check_undervoltage(voltage)) {
            // Fail if the voltage is less than the undervoltage threshold
            printf("Test Result: Fail (Undervoltage Detected)\n");
        } else if (check_overvoltage(voltage)) {
            // Fail if the voltage is greater than the overvoltage threshold
            printf("Test Result: Fail (Overvoltage Detected)\n");
        } else {
            // Pass if the voltage is within the acceptable range
            printf("Test Result: Pass\n");
        }
    }

    return 0;
}
