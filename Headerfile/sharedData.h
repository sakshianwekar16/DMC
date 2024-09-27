/*
 * sharedData.h
 *
 *  Created on: Sep 19, 2024
 *      Author: Admin
 */
#include<stdint.h>
#include"initialconfig.h"
#ifndef HEADERFILE_SHAREDDATA_H_
#define HEADERFILE_SHAREDDATA_H_

// Define a structure to hold current measurement parameters
typedef struct {
    float filtered_current; // Filtered current value
    float current;
    float voltage;// Raw current value
    float SHUNT_RESISTOR;   // Shunt resistor value
    float GAIN; 
	float temperature;            // Gain factor
    uint32_t ADC_RESOLUTION; // ADC resolution
    float REFERENCE_VOLTAGE; // Reference voltage
    float OVER_VOLTAGE_THRESHOLD; // Over voltage threshold
    float UNDER_VOLTAGE_THRESHOLD; // Under voltage threshold
    uint32_t CURRENT_THRESHOLD;
	float TEMPERATURE_THRESHOLD; // Current threshold
    uint32_t THROTTLE_START_ADC; // ADC value for throttle start
    uint32_t MAX_RPM;        // Maximum RPM
    uint32_t R1;             // Resistance R1
    uint32_t R2;
    uint32_t FILTER_SHIFT;
    uint32_t ADC_MAX_VALUE;
	uint32_t target_rpm;
	float V25;
	float VSENSE;
	float AVG_SLOPE;// Resistance R2
}FIXED_VALS_t;
extern FIXED_VALS_t Fixedvalue;

typedef struct {
	uint16_t raw;
	uint16_t filtered;
	int32_t calculated;
} ADC_DATA_t;
extern ADC_DATA_t adcvalue;

typedef struct {
	ADC_DATA_t Current, Voltage, throttle,temperature;
	uint8_t brakeRaw, brake;
	uint8_t hallPosition;
} MEASURED_t;
extern MEASURED_t Measured;

typedef struct {
	union {
		struct{
			uint16_t hallInvalid : 1;
			uint16_t stall : 1;
			uint16_t throttle : 1;
			uint16_t : 1;
			uint16_t underVolt : 1;
			uint16_t overVolt : 1;
			uint16_t : 1;
			uint16_t overCurrent : 1;
			uint16_t : 1;
			uint16_t overTemperature : 1;
			uint16_t : 1;
			uint16_t : 1;
			uint16_t : 1;
			uint16_t : 1;
			uint16_t : 1;
			uint16_t : 1;
		};
		uint16_t value;
	} faults;
} PROTECTION_t;
extern PROTECTION_t Protection;

#endif /* HEADERFILE_SHAREDDATA_H_ */
