#ifndef VOLTAGE_FUNCTIONS_H
#define VOLTAGE_FUNCTIONS_H

// Function prototypes
double calculate_voltage(unsigned int adc_value);
void run_test_case(unsigned int adc_value);

// Define constants
#define ADC_RESOLUTION 4096
#define REFERENCE_VOLTAGE 3.3
#define OVER_VOLTAGE_THRESHOLD 48.0
#define UNDER_VOLTAGE_THRESHOLD 28.0

// Voltage divider resistances
extern const double R1;
extern const double R2;

#endif // VOLTAGE_FUNCTIONS_H
