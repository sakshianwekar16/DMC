#include <stdio.h>

// Function declarations
int check_throttle(int throttle);

// Function to run a test case and print the result
void run_test_case(int throttle, int expected) {
    int result = check_throttle(throttle);
    if (result == expected) {
        printf("Throttle %d -> Result: %d -> Pass\n", throttle, result);
    } else {
        printf("Throttle %d -> Result: %d -> Fail\n", throttle, result, expected);
    }
}

// Main function to call test cases
int main() {
    // Test cases
    run_test_case(700, 0);   // Expected to pass (result should be 0)
    run_test_case(750, 0);   // Expected to pass (result should be 0)
    run_test_case(800, 0);   // Expected to pass (result should be 0)
    run_test_case(850, 1);   // Expected to pass (result should be 1)
    run_test_case(900, 1);   // Expected to pass (result should be 1)
    run_test_case(1000, 1);  // Expected to pass (result should be 1)
    
    return 0;
}
