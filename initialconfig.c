/*
 * initialconfig.c
 *
 *  Created on: Sep 25, 2024
 *      Author: pc
 */
#include"stdint.h"
#include"sharedData.h"
#include"initialconfig.h"
FIXED_VALS_t Fixedvalue;
MEASURED_t Measured;

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
	Fixedvalue.TEMPERATURE_THRESHOLD =90.0;
	Fixedvalue.THROTTLE_START_ADC = 1000;
	Fixedvalue.MAX_RPM = 1300;
	Fixedvalue.R1 = 17380;
	Fixedvalue.R2 = 1000;
	Fixedvalue.FILTER_SHIFT =6;
	Fixedvalue.ADC_MAX_VALUE =4096;
	Fixedvalue.target_rpm = 0;
	Fixedvalue.V25 = 1.43f;
	Fixedvalue.VSENSE = (3.3f/4095.0f);
    Fixedvalue.AVG_SLOPE = 0.0043f;
	Fixedvalue.temperature = 0;

}
