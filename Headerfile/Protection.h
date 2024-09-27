// hall_protection.h

#ifndef HALL_PROTECTION_H
#define HALL_PROTECTION_H

// Function prototype for checking if the input number is between 1 and 6
uint32_t check_hall_protection(uint32_t num);
uint32_t check_throttle(uint32_t rpm);
uint32_t check_overvoltage(uint32_t voltage);
uint32_t check_undervoltage(uint32_t voltage);
uint32_t check_overCurrent(uint32_t current);
uint32_t check_overTemperature(uint32_t temperature);

#endif // HALL_PROTECTION_H
