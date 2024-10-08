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
typedef enum{
	FORWARD = 0U,
	REVERSE = !FORWARD
}DIR_t;

typedef enum {
	SMS_INITIAL = 1U,
	SMS_IDLE = 2U,
	SMS_RUN = 3U,
	SMS_ERROR = 4U,
} STATE_MACHINE_STATE_t;
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
	float AVG_SLOPE;
	uint32_t istimerON_A;
	uint32_t istimerON_B;
	uint32_t istimerON_C;
	uint32_t counter;
	uint32_t islowersideON_A;
	uint32_t islowersideON_B;
	uint32_t islowersideON_C;
	STATE_MACHINE_STATE_t stateMachine_state;
	uint32_t initialAssignmentsCompleted;
	uint16_t hallmodifier;
	DIR_t runDirectionFlag;
	uint16_t phase;
	int32_t phaseoffsetDeg;
	int32_t reverseOffset;
	int32_t forwardOffset;
	int32_t phaseOffset;
	struct phaseAdv{
		uint16_t advanceAngle;
	} phaseAdv;
	uint32_t test_timesOverflowed, times_tim3overflowed;
	uint8_t hall_overflowedFlag;
	uint16_t phaseInc;
	int8_t invertMotor;
	int16_t volts;
	int32_t phaseAdv_baseSpeed;
	int16_t phaseAdv_maxAngle;
	unsigned int PDC1Latch, PDC2Latch, PDC3Latch;
	uint16_t phaseIncAcc;
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
	int32_t brakeRaw, TargetRPM,PhaseA,PhaseB,PhaseC;
	uint8_t hallPosition,hallstate;
	struct motorPeriod{
		uint8_t inputCaptured;
		uint32_t capturedValue;
		uint32_t periodBeforeClamp;
		uint32_t periodBeforeFilter;
		uint32_t period;
		uint8_t firstCap;
		uint32_t lastInputCapturedTime;
	} motorPeriod;

	struct motorSpeed{
		int8_t counter;
		uint32_t acc;
		uint32_t speedWithoutFilter;
		int16_t speed;
	} motorSpeed;
} MEASURED_t;
extern MEASURED_t Measured;


//extern STATE_MACHINE_STATE_t stateMachine;

//typedef struct {
//	// Speed PI
//	int32_t speedPI_kp, speedPI_ki;
//	uint8_t speedPI_sat;
//	int16_t speedPI_error;
//	int16_t speedPI_output;
//	int32_t speedPI_integral;
//	int32_t speedPI_counter;
//	// Current PI
//	int32_t currentPI_kp, currentPI_ki;
//	uint8_t currentPI_sat;
//	int16_t currentPI_error;
//	int16_t currentPI_output;
//	int32_t currentPI_integral;
//	int32_t phaseAdv_angle;
//	uint8_t flag_sixStep;
//	uint32_t runCounter;
//
//	uint32_t timerDivCount;
//} CONTROL_VALUE_t;
//extern CONTROL_VALUE_t ControlVals;

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
