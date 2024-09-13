// voltage_main.c
#include <stdio.h>

// Function prototypes
double calculate_voltage(unsigned int adc_value);
int check_overvoltage(double voltage);
int check_undervoltage(double voltage);

// Function to run a test case
void run_test_case(unsigned int adc_value) {
    double voltage = calculate_voltage(adc_value);

    // Print the calculated voltage for debugging
    printf("ADC Value: %u -> Calculated Voltage: %.2f V\n", adc_value, voltage);

    // Check voltage conditions and print results
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

int main() {
    // Test cases with ADC values
    unsigned int adc_values[] = {0, 100, 125, 225, 300, 425, 512,625,700,800,925, 1024, 1500, 2000, 2048, 3000, 3072, 4096};
    size_t num_tests = sizeof(adc_values) / sizeof(adc_values[0]);

    for (size_t i = 0; i < num_tests; i++) {
        run_test_case(adc_values[i]);
    }

    return 0;
}
