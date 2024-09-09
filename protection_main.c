#include <stdio.h>

// Function declarations
int check_hall_protection(unsigned int num);

// Function to run a test case and print the result
void run_test_case(unsigned int num, int expected) {
    int result = check_hall_protection(num);
    if (result == expected) {
        printf("Input %u -> Result: %d -> Pass\n", num, result);
    } else {
        printf("Input %u -> Result: %d -> Fail (Expected: %d)\n", num, result, expected);
    }
}

// Main function to call test cases
int main() {
    // Test cases
    run_test_case(0, 0);   
    run_test_case(1, 1);   
    run_test_case(2, 1);  
    run_test_case(3, 1);   
    run_test_case(4, 1);   
    run_test_case(5, 1);   
    run_test_case(6, 1);  
    run_test_case(7, 0);   
    
    return 0;
}
