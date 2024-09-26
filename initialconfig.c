/*
 * initialconfig.c
 *
 *  Created on: Sep 25, 2024
 *      Author: pc
 */
//#define ADC_RESOLUTION 4096
//#define REFERENCE_VOLTAGE 3.3
//#define OVER_VOLTAGE_THRESHOLD 48.0
//#define UNDER_VOLTAGE_THRESHOLD 28.0
//#define SHUNT_RESISTOR 0.005
//#define GAIN 8.5
//#define CURRENT_THRESHOLD 20
//#define FILTER_SHIFT 6
//#define ADC_MAX_VALUE 4096
//#define THROTTLE_START_ADC 1000
//#define MAX_RPM 1300
//// extern const uint32_t R1;
//// extern const uint32_t R2;
//#define R1 17380
//#define R2 1000

#include"stdint.h"
#include"sharedData.h"
#include"initialconfig.h"
FIXED_VALS_t Fixedvalue;

void initialvalueassignment(void){
	Fixedvalue.filtered_current = 0.0f;
	Fixedvalue.current = 0.0f;
	Fixedvalue.voltage = 0.0f;
	Fixedvalue.SHUNT_RESISTOR = 0.005;
	Fixedvalue.GAIN = 8.5;
	Fixedvalue.ADC_RESOLUTION = 4096;
	Fixedvalue.REFERENCE_VOLTAGE = 3.3;
	Fixedvalue.OVER_VOLTAGE_THRESHOLD = 48.0;
	Fixedvalue.UNDER_VOLTAGE_THRESHOLD = 28.0;
	Fixedvalue.CURRENT_THRESHOLD = 20.0;
	Fixedvalue.THROTTLE_START_ADC = 1000;
	Fixedvalue.MAX_RPM = 1300;
	Fixedvalue.R1 = 17380;
	Fixedvalue.R2 = 1000;
	Fixedvalue.FILTER_SHIFT =6;
	Fixedvalue.ADC_MAX_VALUE =4096;
}
