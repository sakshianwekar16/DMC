#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

extern double filtered_current;
extern double current;
extern double voltage;
extern uint32_t rpm;
extern uint32_t hall_position;
extern uint32_t brake;

// Define the number of ADC and Hall position values
#define NUM_ADC_VALUES 13
#define NUM_HALL_POSITIONS 8

// Function declarations
uint32_t read_adc_value(void);
uint32_t get_hall_position(void);
void set_adc_index(int index);
void set_hall_index(int index);

#endif // INPUT_H
