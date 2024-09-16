// current_measurement.h

#ifndef CURRENT_MEASUREMENT_H
#define CURRENT_MEASUREMENT_H

// Constants for current measurement
#define ADC_RESOLUTION 4096      // 12-bit ADC resolution (0 to 4095)
#define REFERENCE_VOLTAGE 3.3     // Reference voltage in volts
#define SHUNT_RESISTOR 0.005      // Shunt resistor value in ohms
#define GAIN 8.5                  // Gain factor for current measurement
#define CURRENT_THRESHOLD 20.0    // Maximum allowed current value in amperes
#define FILTER_SHIFT 6            // Bit shift for filtering (equivalent to dividing by 64)

// Function declarations

/**
 * @brief Setup function for current measurement.
 *
 * This function is a placeholder for any future configuration required for
 * current measurement. Currently, it does not perform any actions.
 */
void setup_currentMeasurementValues(void);

/**
 * @brief Calculates the current based on ADC value and applies filtering.
 *
 * This function computes the actual current value using a low-pass filter to
 * smooth out the ADC measurements. It then compares the computed current with
 * a predefined threshold to determine if it is within the acceptable range.
 *
 * @param adc_value The ADC value representing the current measurement.
 * @return 1 if the current is within the acceptable range, 0 otherwise (indicating a failure).
 */
unsigned calculateCurrent(unsigned int adc_value);

#endif // CURRENT_MEASUREMENT_H
