/*
 * initialconfig.c
 *
 *  Created on: Sep 25, 2024
 *      Author: pc
 */
#include"stdint.h"
#include"sharedData.h"
#include"initialconfig.h"
FIXED_VALS_t FixedValue;
//MEASURED_t Measured;
void initialconfiguration(){
	FixedValue.initialAssignmentsCompleted = 0;
	initialvalueassignment();
	FixedValue.initialAssignmentsCompleted = 1;

}


void initialvalueassignment(void){

	//current calculation
	FixedValue.filtered_current = 0.0;
	FixedValue.current_nominal = 1400;
	FixedValue.current = 0.0f;
	FixedValue.shunt_resistor = 0.005;
	FixedValue.gain = 8.5;
	FixedValue.filter_shift =6;

	//voltage calculation
	FixedValue.voltage = 0.0f;
	FixedValue.r1 = 20000;
	FixedValue.r2 = 1200;
	FixedValue.adcResolution = 4096;
	FixedValue.ref_voltage = 3.3f;

	//Threshold values
	FixedValue.over_voltage_threshold= 48.0;
	FixedValue.under_voltage_threshold = 28.0;
	FixedValue.current_threshold = 20.0;
	FixedValue.temperature_threshold = 90.0;
	FixedValue.throttle_start_adc = 1300;
	FixedValue.max_rpm = 1300;
	FixedValue.adc_max_value =4096;
	FixedValue.maxRPMLimit = 922;

	//Temperature calculation
	FixedValue.v25 = 1.43;
	FixedValue.vsense = (3.3/4095);
    FixedValue.avg_slope = 0.0043;
	FixedValue.temperature = 0;

	//Motor calculation
	MotorRun.hallmodifier = 0;
	MotorRun.phaseoffsetDeg = 170U;
	MotorRun.phaseOffset = (int32_t)(((float)MotorRun.phaseoffsetDeg/360.0)*65536.0);
	MotorRun.reverseOffset = 65536 - MotorRun.phaseOffset;
	MotorRun.forwardOffset = MotorRun.phaseOffset;
	MotorRun.invertMotor = 0;


	// For control loop
	FixedValue.controlPI.speedPI_kp_highRPM = 8000;
	FixedValue.controlPI.speedPI_kp_lowRPM = 8000;
	FixedValue.controlPI.speedPI_ki_highRPM = 2;
	FixedValue.controlPI.speedPI_ki_lowRPM = 2;
	FixedValue.controlPI.speedPI_lowRPMShelf = 100;
	FixedValue.controlPI.speedPI_highRPMShelf = 350;
	FixedValue.controlPI.speedPI_scale = 12;
	FixedValue.controlPI.speedPI_maxCounter = 10;
    FixedValue.controlPI.speedPI_kp = 8000;
    FixedValue.controlPI.speedPI_ki = 2;
	FixedValue.controlPI.currentPI_kp = 6000;
	FixedValue.controlPI.currentPI_ki = 20;
	FixedValue.controlPI.currentPI_scale = 14;

	// Gain Scheduling
	FixedValue.controlPI.speedPI_schMulSc = 5;
	float n = FixedValue.controlPI.speedPI_kp_lowRPM - FixedValue.controlPI.speedPI_kp_highRPM;
	float p = FixedValue.controlPI.speedPI_highRPMShelf - FixedValue.controlPI.speedPI_lowRPMShelf;
	FixedValue.controlPI.speedPI_schMul = (int32_t)(n/p) * (1 << FixedValue.controlPI.speedPI_schMulSc);


	//pedal Assist
//	uint32_t temp_maxRPMLimit = 922;
//	uint16_t temp_pedal0 = 0;
//	uint16_t temp_pedal1 = (uint16_t)((temp_maxRPMLimit * 14)/25);
//	uint16_t temp_pedal2 = (uint16_t)((temp_maxRPMLimit * 16)/25);
//	uint16_t temp_pedal3 = (uint16_t)((temp_maxRPMLimit * 18)/25);
//	uint16_t temp_pedal4 = (uint16_t)((temp_maxRPMLimit * 22)/25);
//	uint16_t temp_pedal5 = (uint16_t)temp_maxRPMLimit;

	PedalAssist.addAmount = 100;
	PedalAssist.derampFactor = 10;
	PedalAssist.minDiff = 50;
	PedalAssist.maxDiff = 1000;
	PedalAssist.scale = 12;
	PedalAssist.timeout = 1500;
	PedalAssist.maxRPM = 1300;


	//Cruise control
	// Cruise mode
	CruiseMode.throttleMoveThreshold = 100;		// Throttle movement detection threshold
	CruiseMode.timeToSetAutoCruise = 4000;		// Time required for auto cruise to set
	CruiseMode.cruiseSetBaseValue = 400;

}
