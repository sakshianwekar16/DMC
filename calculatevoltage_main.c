#include <stdio.h>
#include <math.h>

// Function to calculate the input voltage based on ADC value
double calculate_voltage(unsigned int adc_value);

// Tolerance for floating-point comparison
#define TOLERANCE 0.3

// Function to compare expected and calculated voltage
void run_voltage_tests(void) {
    // Define test cases with expected results
    struct {
        unsigned int adc_value;
        double expected_voltage;
    } test_cases[] = {
        {0, 0.00},          // ADC value 0 -> Voltage 0.00 V
        {100, 3.61},        // Expected voltage for ADC value 100
        {125, 4.05},        // Expected voltage for ADC value 125
        {200, 7.48},        // Expected voltage for ADC value 200
        {250, 9.17},        // Expected voltage for ADC value 250
        {325, 11.93},       // Expected voltage for ADC value 325
        {450, 16.43},
        {512,18.53},
        {800,28.97},       // Expected voltage for ADC value 450
        {1024,37.001},      // Expected voltage for ADC value 1024
        {2048, 74.27},      // Expected voltage for ADC value 2048
        {3000, 108.58},     // Expected voltage for ADC value 3000
        {3072, 111.05},     // Expected voltage for ADC value 3072
        {4095, 147.99}      // Expected voltage for ADC value 4095
    };

    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; i++) {
        unsigned int adc_value = test_cases[i].adc_value;
        double expected_voltage = test_cases[i].expected_voltage;
        double calculated_voltage = calculate_voltage(adc_value);

        // Print the ADC value and the calculated voltage
        printf("ADC Value: %u -> Calculated Voltage: %.2f V\n", adc_value, calculated_voltage);

        // Check if the first digit (integer part) of the calculated and expected voltage match
        int expected_integer_part = (int)expected_voltage;
        int calculated_integer_part = (int)calculated_voltage;

        if (expected_integer_part == calculated_integer_part) {
            printf("Test Result: Pass\n");
        } else {
            printf("Test Result: Fail (Expected Voltage: %.2f V, Calculated Voltage: %.2f V)\n",
                   expected_voltage, calculated_voltage);
        }
    }
}

int main(void) {
    // Call test functions
    run_voltage_tests();
    return 0;
}
