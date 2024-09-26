#ifndef TASKHANDLER_H
#define TASKHANDLER_H

#include <stdint.h>



// External variable declarations
//extern uint32_t filtered_current;
//extern uint32_t current;
//extern uint32_t voltage;
//extern uint32_t rpm;
//extern uint32_t hall_position;
//extern uint32_t brake;

//#define ADC_RESOLUTION 4096
//#define REFERENCE_VOLTAGE 3.3
//#define OVER_VOLTAGE_THRESHOLD 48.0
//#define UNDER_VOLTAGE_THRESHOLD 28.0
//#define SHUNT_RESISTOR 0.005
//#define GAIN 8.5
//#define CURRENT_THRESHOLD 20.0
//#define FILTER_SHIFT 6
//#define ADC_MAX_VALUE 4096
//#define THROTTLE_START_ADC 1000
//#define MAX_RPM 1300

// Function prototypes
//void setup_currentMeasurementValues(void);
//uint32_t calculate_current(uint32_t adc_value);
//uint32_t calculate_voltage(uint32_t adc_value);
//uint32_t check_overvoltage(uint32_t voltage);
//uint32_t check_undervoltage(uint32_t voltage);
//uint32_t check_throttle(uint32_t rpm);
//uint32_t calculate_rpm(uint32_t adc_value, uint32_t max_rpm);
//uint32_t read_adc_value(void);
//uint32_t adc_to_rpm(uint32_t adc_value, uint32_t max_rpm, uint32_t adc_max_value, uint32_t throttle_start_adc);
//uint32_t check_hall_protection(uint32_t num);
void update_ADC(uint32_t current,uint32_t voltage,uint32_t throttle);
void handle_hall(uint8_t hall);
//uint32_t get_hall_position(void);
//uint32_t get_brakestatus(void);
//uint32_t check_overCurrent(current);
void slow_loop(void);
void fast_loop(void);

#endif // TASKHANDLER_H
