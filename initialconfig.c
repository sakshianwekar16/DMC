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
FIXED_VALS_t fixedvalue;

void initialvalueassignment(void){
	fixedvalue.filtered_current = 0.0f;
	fixedvalue.current = 0.0f;
	fixedvalue.voltage = 0.0f;
	fixedvalue.SHUNT_RESISTOR = 0.005;
	fixedvalue.GAIN = 8.5;
	fixedvalue.ADC_RESOLUTION = 4096;
	fixedvalue.REFERENCE_VOLTAGE = 3.3;
	fixedvalue.OVER_VOLTAGE_THRESHOLD = 48.0;
	fixedvalue.UNDER_VOLTAGE_THRESHOLD = 28.0;
	fixedvalue.CURRENT_THRESHOLD = 20.0;
	fixedvalue.THROTTLE_START_ADC = 1000;
	fixedvalue.MAX_RPM = 1300;
	fixedvalue.R1 = 17380;
	fixedvalue.R2 = 1000;
	fixedvalue.FILTER_SHIFT =6;
	fixedvalue.ADC_MAX_VALUE =4096;
}
