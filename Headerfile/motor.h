#include<stdint.h>
#ifndef MOTOR_H
#define MOTOR_H

int32_t get_PHASEA_PWM_Value();
int32_t get_PHASEB_PWM_Value();
int32_t get_PHASEC_PWM_Value();
void phaseAdv_updateAngle(void);
void motor_sineCommutation(void);


#endif
