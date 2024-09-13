#include <stdio.h>
#include <math.h>
void  run_rpm_tests(void) {
    // Define test cases with expected results
    struct {
        int adc_value;
        int expected_rpm;
    } test_cases[] = {
        {0, 0},            // ADC value 0 -> RPM 0
        {887, 0},          // ADC value 887 -> RPM 0 (below throttle start)
        {1000, 0},         // ADC value 1000 -> RPM 0 (throttle start)
        {1300, 125},         // ADC value 1300 -> RPM 0 (throttle start, but no RPM)
        {1775, 325},       // ADC value 1775 -> RPM (1775 - 1000) / (4096 - 1000) * 1300
        {2662, 697},       // ADC value 2662 -> RPM (2662 - 1000) / (4096 - 1000) * 1300
        {3550, 1070},      // ADC value 3550 -> RPM (3550 - 1000) / (4096 - 1000) * 1300
        {4096, 1300}       // ADC value 4096 -> RPM 1300
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    int dynamic_max_rpm = 1300; // Example maximum RPM

    printf("Running RPM test cases...\n");
    for (int i = 0; i < num_tests; i++) {
        int rpm = calculate_rpm(test_cases[i].adc_value, dynamic_max_rpm);
        if (rpm == test_cases[i].expected_rpm) {
            printf("Test %d: ADC Value %d -> RPM %d -> Pass\n",
                   i + 1, test_cases[i].adc_value, rpm);
        } else {
            printf("Test %d: ADC Value %d -> RPM %d -> Fail (Expected: %d)\n",
                   i + 1, test_cases[i].adc_value, rpm, test_cases[i].expected_rpm);
        }
    }
}

int main(void) {
    // Call test functions
    run_rpm_tests();
    return 0;
}



