/*
 * motor.c
 *
 *  Created on: Sep 27, 2024
 *      Author: pc
 */
#include<stdint.h>
#include"brake.h"
#include"measurement.h"
#include"initialconfig.h"
#include"sharedData.h"
#include"taskhandler.h"
#include"motor.h"

uint32_t get_PHASEA_PWM_Value(){

	 return Measured.TargetRPM;
}

uint32_t get_PHASEB_PWM_Value(){

	 return Measured.TargetRPM;
}

uint32_t get_PHASEC_PWM_Value(){

	 return Measured.TargetRPM;
}
