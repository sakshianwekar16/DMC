// main.c
#include <stdint.h>
#include <stdio.h>

// Declare the extern variable for current
extern double current;

// Declarations for functions in Protection.c
void setup_currentMeasurementValues(void);
int calculateCurrent(unsigned int adc_value);

// Test the current measurement function
int main() {
    // Initialize current measurement values
    setup_currentMeasurementValues();

    // Example ADC values for testing
    unsigned int adc_values[] = {0, 100, 125, 200, 250, 325, 450, 1024, 2048, 3000, 3072, 4095}; // Example ADC values
    size_t num_tests = sizeof(adc_values) / sizeof(adc_values[0]);

    for (size_t i = 0; i < num_tests; i++) {
        // Calculate whether the current exceeds the threshold
        int result = calculateCurrent(adc_values[i]);
        
        // Print the measured current and test result
        if (result == 0) {
            printf("ADC Value: %u -> Measured Current: %.2f A -> Fail (Overcurrent detected)\n", adc_values[i], current);
        } else {
            printf("ADC Value: %u -> Measured Current: %.2f A -> Pass (Current is within acceptable range)\n", adc_values[i], current);
        }
    }

    return 0;
}
