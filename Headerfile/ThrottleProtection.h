// test_throttle.h

#ifndef TEST_THROTTLE_H
#define TEST_THROTTLE_H
#include <stdint.h>
// Function declarations

/**
 * @brief Checks if the throttle value exceeds a specified limit.
 *
 * This function compares the provided throttle value against a predefined
 * protection limit (800). If the throttle value exceeds the limit, the
 * function returns 1. Otherwise, it returns 0.
 *
 * @param throttle The throttle value to check.
 * @return 1 if the throttle exceeds the protection limit, 0 otherwise.
 */
uint32_t check_throttle(uint32_t throttle);

/**
 * @brief Runs a test case for the check_throttle function and prints the result.
 *
 * This function calls the check_throttle function with the provided throttle value,
 * compares the result with the expected value, and prints whether the test case passed
 * or failed.
 *
 * @param throttle The throttle value to test.
 * @param expected The expected result of the test case.
 */
void run_test_case(int throttle, int expected);

#endif // TEST_THROTTLE_H
