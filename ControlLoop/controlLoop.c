/*
 * controlLoop.c
 *
 *  Created on: Oct 8, 2024
 *      Author: pc
 */

#include"sharedData.h"
#include"initialconfig.h"
#include"controlLoop.h"

controlLoop_t ControlVals;
void updateSpeedPIValues(void){
	int16_t r = (int16_t)Measured.TargetRPM;

	// for Kp
	if (r > FixedValue.controlPI.speedPI_highRPMShelf){
		ControlVals.speedPI_kp= FixedValue.controlPI.speedPI_kp_highRPM;
	} else if (r > FixedValue.controlPI.speedPI_lowRPMShelf){
		int32_t uniqueDiff = FixedValue.controlPI.speedPI_highRPMShelf - r;
		ControlVals.speedPI_kp = ((uniqueDiff * FixedValue.controlPI.speedPI_schMul) >> FixedValue.controlPI.speedPI_schMulSc) + FixedValue.controlPI.speedPI_kp_highRPM;
	} else {
		ControlVals.speedPI_kp = FixedValue.controlPI.speedPI_kp_lowRPM;
	}

	// for Ki
	ControlVals.speedPI_ki = FixedValue.controlPI.speedPI_ki_lowRPM;
}

// To get the Iref value
void speedPI(){
	ControlVals.speedPI_error = (int32_t)Measured.TargetRPM - Measured.motorSpeed.speed;
//	controlVals.speedPI_error = (int32_t)controlVals.targetRPM - 0;
	ControlVals.speedPI_integral += (int32_t)ControlVals.speedPI_error * (int32_t)ControlVals.speedPI_ki * (int32_t)ControlVals.speedPI_sat;
	int16_t controlSignal = (int32_t)((ControlVals.speedPI_error * ControlVals.speedPI_kp) + ControlVals.speedPI_integral) >> FixedValue.controlPI.speedPI_scale;

	if (controlSignal > (int16_t)FixedValue.current_nominal){
		ControlVals.speedPI_output = (int16_t)FixedValue.current_nominal;
		ControlVals.speedPI_sat = 0U;
	} else if (controlSignal < -(int16_t)FixedValue.current_nominal){
		ControlVals.speedPI_output = -(int16_t)FixedValue.current_nominal;
		ControlVals.speedPI_sat = 0U;
	} else {
		ControlVals.speedPI_output = controlSignal;
		ControlVals.speedPI_sat = 1U;
	}
}

// To get the "volts" value
void currentPI(){
	if (0 == Measured.TargetRPM){
		ControlVals.currentPI_integral = 0;
	}
	ControlVals.currentPI_error = (int32_t)ControlVals.speedPI_output - (int32_t)Measured.Current.calculated;
//	controlVals.currentPI_error = (int32_t)controlVals.speedPI_output - (int32_t)0;		// bypassing current
	ControlVals.currentPI_integral += (int32_t)ControlVals.currentPI_error * (int32_t)FixedValue.controlPI.currentPI_ki * (int32_t)ControlVals.currentPI_sat;
	int32_t controlSignal = (int32_t)((ControlVals.currentPI_error * FixedValue.controlPI.currentPI_kp) + ControlVals.currentPI_integral) >> FixedValue.controlPI.currentPI_scale;

	if (controlSignal > 32767){				// this 32767 value should be verified asap
		ControlVals.currentPI_output = 32767;
		ControlVals.currentPI_sat = 0U;
	} else if (controlSignal < 0){
		ControlVals.currentPI_output = 0;
		ControlVals.currentPI_sat = 0U;
	} else {
		ControlVals.currentPI_output = controlSignal;
		ControlVals.currentPI_sat = 1U;
	}

}


// Handle the control loop in one function.
void controlLoop_run(){
	// To run speedPI slower than currentPI
	ControlVals.speedPI_counter++;
	if (ControlVals.speedPI_counter >= FixedValue.controlPI.speedPI_maxCounter){
		speedPI();
		ControlVals.speedPI_counter = 0;
	}
	currentPI();
}

// Reset the control loop
void controlLoop_reset(){
	ControlVals.speedPI_output = 0;
	ControlVals.speedPI_integral = 0;
	ControlVals.currentPI_output = 0;
	ControlVals.currentPI_integral = 0;
	ControlVals.speedPI_counter = 0;
}

