#ifndef TASKHANDLER_H
#define TASKHANDLER_H

#include <stdint.h>



void update_ADC(uint32_t current,uint32_t voltage,uint32_t throttle,uint32_t temperature);
void update_brakevalue(uint32_t brake);
void handle_hall(uint8_t hall);
//uint32_t get_hall_position(void);
//uint32_t get_brakestatus(void);
//uint32_t check_overCurrent(current);
void slow_loop(void);
void fast_loop(void);


#endif // TASKHANDLER_H
