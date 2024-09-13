// main.c
#include <stdio.h>

// Function prototypes
int read_adc_value(void);
int calculate_rpm(int adc_value, int max_rpm);
void update_throttle(int brake, int *throttle, int max_rpm);

// Function to test the update_throttle function
void test_brake_function(int brake_value, int expected_throttle, int max_rpm) {
    int throttle;
    
    // Call the update_throttle function
    update_throttle(brake_value, &throttle, max_rpm);

    if (throttle == expected_throttle) {
        printf("Test Passed: brake(%d) resulted in throttle(RPM) %d\n", brake_value, throttle);
    } else {
        printf("Test Failed: brake(%d) resulted in throttle(RPM) %d, expected %d\n", brake_value, throttle, expected_throttle);
    }
}

int main() {
    int max_rpm = 6000; // Example maximum RPM value

    // Read ADC value
    int adc_value = read_adc_value();
    
    // Calculate RPM based on ADC value
    int rpm = calculate_rpm(adc_value, max_rpm);

    // Test case 1: Brake applied
    int brake_value = 1; // Simulate brake applied
    int expected_throttle = 0; // Throttle should be 0 if brake is applied
    test_brake_function(brake_value, expected_throttle, max_rpm);

    // Test case 2: Brake not applied
    brake_value = 0; // Simulate no brake applied
    expected_throttle = rpm; // Throttle should be RPM value if brake is not applied
    test_brake_function(brake_value, expected_throttle, max_rpm);

    // Determine final throttle value
    int throttle = brake_value ? 0 : rpm; // Set throttle to 0 if brake is applied, otherwise use RPM

    // Print results
    printf("ADC Value: %d\n", adc_value);
    printf("Calculated RPM: %d\n", rpm);
    printf("Final Throttle value: %d\n", throttle);

    return 0;
}
