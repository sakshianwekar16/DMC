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


    //Throttle values
    uint32_t adcResolution, throttle_start_adc, max_rpm, maxRPMLimit;

    //Threshold Values
    uint32_t ref_voltage, over_voltage_threshold, under_voltage_threshold, current_threshold, temperature_threshold; // Reference voltage

    //current calculation
    int32_t filtered_current, current_calibrationFactor;
    uint32_t current_nominal, filter_shift;

    //voltage calculation
    uint32_t r1, r2;
    uint32_t adc_max_value;

    //temperature caculation
	float v25;
	float vsense;
	float avg_slope;

	//stateMachine
	uint32_t istimerON_A, istimerON_B, istimerON_C; //high side timer
	uint32_t counter;
	uint32_t islowersideON_A, islowersideON_B, islowersideON_C;

	//motor parameter
	int32_t phaseAdv_baseSpeed;
	int16_t phaseAdv_maxAngle;
	int32_t phaseoffsetDeg;
	int8_t invertMotor;
	int8_t hallmodifier;

	struct controlPI{
		int32_t speedPI_kp_lowRPM, speedPI_kp_highRPM;
		int32_t speedPI_ki_lowRPM, speedPI_ki_highRPM;
		int32_t speedPI_lowRPMShelf, speedPI_highRPMShelf;
		int32_t speedPI_schMul, speedPI_schMulSc;
		uint32_t speedPI_maxCounter;
		uint8_t speedPI_scale;
		uint32_t speedPI_kp;
		uint32_t speedPI_ki;
		int32_t currentPI_kp, currentPI_ki;
		uint8_t currentPI_scale;
	}controlPI;

}FIXED_VALS_t;
extern FIXED_VALS_t FixedValue;

typedef struct {
	uint16_t raw;
	uint16_t filtered;
	int32_t calculated;
} ADC_DATA_t;
extern ADC_DATA_t AdcValue;

typedef struct{
	uint8_t hallstate;
	DIR_t runDirectionFlag;
	uint16_t phase;
	int32_t reverseOffset;
	int32_t forwardOffset;
	int32_t phaseOffset;
	uint32_t test_timesOverflowed, times_tim3overflowed;
	uint8_t hall_overflowedFlag;
	struct phaseAdv{
		uint16_t advanceAngle;
	} phaseAdv;
	uint16_t phaseInc;
	int16_t volts;
	uint16_t phaseIncAcc;
	uint16_t PDC1Latch;
	uint16_t PDC2Latch;
	uint16_t PDC3Latch;
	uint16_t counter;
}MotorRun_t;
extern MotorRun_t MotorRun;

typedef struct {
	uint32_t lastTick, diff;
	uint32_t addAmount;
	uint16_t maxDiff, minDiff, timeout;
	uint8_t scale;
	int16_t value;
	int16_t targetRPM;
	int16_t maxRPM;
	uint8_t level, prevLevel;
	uint16_t mode0RPM, mode1RPM, mode2RPM, mode3RPM, mode4RPM, mode5RPM;
	uint32_t derampFactor;
} PEDAL_ASSIST_t;
extern PEDAL_ASSIST_t PedalAssist;

typedef struct controlLoop{
	int32_t speedPI_kp, speedPI_ki;
	uint8_t speedPI_sat;
	int16_t speedPI_error;
	int16_t speedPI_output;
	int32_t speedPI_integral;
	int32_t speedPI_counter;
	// Current PI
	int32_t currentPI_kp, currentPI_ki;
	uint8_t currentPI_sat;
	int16_t currentPI_error;
	int16_t currentPI_output;
	int32_t currentPI_integral;

	STATE_MACHINE_STATE_t stateMachine_state;
	uint32_t initialAssignmentsCompleted;
}controlLoop_t;
extern controlLoop_t ControlVals;

typedef struct {
	ADC_DATA_t Current, Voltage, throttle,temperature;
	int32_t brakeRaw, TargetRPM,PhaseA,PhaseB,PhaseC;
	uint8_t hallPosition;
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

	struct singleWireSpeed{
		uint32_t rawTickDiff;
		uint32_t lastTick;
		uint32_t tickDiff;
		uint32_t tk;// uint32_t should not be required
	} singleWireSpeed;
} MEASURED_t;
extern MEASURED_t Measured;



typedef struct {
	struct in{
//		uint8_t rxBuf[DISPLAY_RX_SIZE];
//		uint8_t rawData[DISPLAY_RX_SIZE];
		struct parsed{
			uint8_t pedalAssist;
			union{
				struct{
					uint8_t cruiseSignal: 1;
					uint8_t manualCruise : 1;
					uint8_t : 3;
					uint8_t light : 1;
					uint8_t : 2;
				};
				uint8_t value;
			} multiParam;
		} parsed;
	} in;
	struct out {
		union {
			struct {
				uint8_t :2;
				uint8_t cruise :1;
				uint8_t voltage :1;
				uint8_t ECUError :1;
				uint8_t throttle :1;
				uint8_t motor :1;
				uint8_t walkAssist :1;
			};
			uint8_t code;
		} errorCode8;
		uint8_t brake, current;
	} out;
	uint32_t lastReceptionTime, lastReconnectionAttempt;
} DISPLAY_VAL_t;
extern DISPLAY_VAL_t Display;

typedef struct {
	int16_t lastThrottle;
	int16_t throttleMoveThreshold;
	int16_t delta;
	int16_t throttleBaseValue;
	uint32_t throttleBaseValueSetTime;
	int16_t timeToSetAutoCruise;
	int16_t cruiseSetBaseValue;
	uint32_t setTime;
	uint32_t setInterval;
	uint32_t t;
	uint32_t speed;
	union{
		struct{
			uint8_t isCruising : 1;
			uint8_t isInManualCruise : 1;
			uint8_t isInAutoCruise : 1;
			uint8_t displayManualCriuseLastState : 1;
			uint8_t : 4;
		};
		uint8_t value;
	} flags;
} CRUISE_MODE_t;
extern CRUISE_MODE_t CruiseMode;

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
