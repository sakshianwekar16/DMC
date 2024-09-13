#include <stdio.h>
#include <math.h>
extern double current;

void run_current_tests(void) {
    // Define test cases with expected results
    struct {
        unsigned int adc_value;
        double expected_current;
    } test_cases[] = {
        {0, 0.0},            // ADC value 0 -> Current 0.0 A
        {100, 0.03},         // Expected current for ADC value 100
        {125, 0.07},         // Expected current for ADC value 125
        {200, 0.12},         // Expected current for ADC value 200
        {250, 0.20},         // Expected current for ADC value 250
        {325, 0.29},         // Expected current for ADC value 325
        {450, 0.42},         // Expected current for ADC value 450
        {1024, 0.72},        // Expected current for ADC value 1024
        {2048, 1.31},        // Expected current for ADC value 2048
        {3000, 2.18},        // Expected current for ADC value 3000
        {3072, 3.06},        // Expected current for ADC value 3072
        {4096, 4.22}         // Expected current for ADC value 4095
    };

    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; i++) {
        unsigned int adc_value = test_cases[i].adc_value;
        double expected_current = test_cases[i].expected_current;

        // Call calculateCurrent function
        calculateCurrent(adc_value);

        // Print the ADC value and the calculated current
        printf("ADC Value: %u -> Calculated Current: %.2f A\n", adc_value, current);

        // Check if the calculated current is within the acceptable tolerance of the expected current
        if (fabs(current - expected_current) < 0.05) {  // Tolerance of 0.05 A
            printf("Test Result: Pass\n");
        } else {
            printf("Test Result: Fail (Expected Current: %.2f A, Calculated Current: %.2f A)\n",
                   expected_current, current);
        }
    }
}

int main(void) {
    // Setup current measurement values if needed
    setup_currentMeasurementValues();

    // Call test functions
    run_current_tests();
    return 0;
}
