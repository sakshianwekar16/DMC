/*
 * controlLoop.c
 *
 *  Created on: Oct 8, 2024
 *      Author: pc
 */

#include"sharedData.h"
#include"initialconfig.h"
#include"controlLoop.h"
void updateSpeedPIValues(void){
	int16_t r = (int16_t)Measured.TargetRPM;

	// for Kp
	if (r > FixedValue.controlPI.speedPI_highRPMShelf){
		Measured.controlLoop.speedPI_kp= FixedValue.controlPI.speedPI_kp_highRPM;
	} else if (r > FixedValue.controlPI.speedPI_lowRPMShelf){
		int32_t uniqueDiff = FixedValue.controlPI.speedPI_highRPMShelf - r;
		Measured.controlLoop.speedPI_kp = ((uniqueDiff * FixedValue.controlPI.speedPI_schMul) >> FixedValue.controlPI.speedPI_schMulSc) + FixedValue.controlPI.speedPI_kp_highRPM;
	} else {
		Measured.controlLoop.speedPI_kp = FixedValue.controlPI.speedPI_kp_lowRPM;
	}

	// for Ki
	Measured.controlLoop.speedPI_ki = FixedValue.controlPI.speedPI_ki_lowRPM;
}

// To get the Iref value
void speedPI(){
	Measured.controlLoop.speedPI_error = (int32_t)Measured.TargetRPM - Measured.motorSpeed.speed;
//	controlVals.speedPI_error = (int32_t)controlVals.targetRPM - 0;
	Measured.controlLoop.speedPI_integral += (int32_t)Measured.controlLoop.speedPI_error * (int32_t)Measured.controlLoop.speedPI_ki * (int32_t)Measured.controlLoop.speedPI_sat;
	int16_t controlSignal = (int32_t)((Measured.controlLoop.speedPI_error * Measured.controlLoop.speedPI_kp) + Measured.controlLoop.speedPI_integral) >> FixedValue.controlPI.speedPI_scale;

	if (controlSignal > (int16_t)FixedValue.current_nominal){
		Measured.controlLoop.speedPI_output = (int16_t)FixedValue.current_nominal;
		Measured.controlLoop.speedPI_sat = 0U;
	} else if (controlSignal < -(int16_t)FixedValue.current_nominal){
		Measured.controlLoop.speedPI_output = -(int16_t)FixedValue.current_nominal;
		Measured.controlLoop.speedPI_sat = 0U;
	} else {
		Measured.controlLoop.speedPI_output = controlSignal;
		Measured.controlLoop.speedPI_sat = 1U;
	}
}

// To get the "volts" value
void currentPI(){
	if (0 == Measured.TargetRPM){
		Measured.controlLoop.currentPI_integral = 0;
	}
	Measured.controlLoop.currentPI_error = (int32_t)Measured.controlLoop.speedPI_output - (int32_t)Measured.Current.calculated;
//	controlVals.currentPI_error = (int32_t)controlVals.speedPI_output - (int32_t)0;		// bypassing current
	Measured.controlLoop.currentPI_integral += (int32_t)Measured.controlLoop.currentPI_error * (int32_t)FixedValue.controlPI.currentPI_ki * (int32_t)Measured.controlLoop.currentPI_sat;
	int32_t controlSignal = (int32_t)((Measured.controlLoop.currentPI_error * FixedValue.controlPI.currentPI_kp) + Measured.controlLoop.currentPI_integral) >> FixedValue.controlPI.currentPI_scale;

	if (controlSignal > 32767){				// this 32767 value should be verified asap
		Measured.controlLoop.currentPI_output = 32767;
		Measured.controlLoop.currentPI_sat = 0U;
	} else if (controlSignal < 0){
		Measured.controlLoop.currentPI_output = 0;
		Measured.controlLoop.currentPI_sat = 0U;
	} else {
		Measured.controlLoop.currentPI_output = controlSignal;
		Measured.controlLoop.currentPI_sat = 1U;
	}

}


// Handle the control loop in one function.
void controlLoop_run(){
	// To run speedPI slower than currentPI
	Measured.controlLoop.speedPI_counter++;
	if (Measured.controlLoop.speedPI_counter >= FixedValue.controlPI.speedPI_maxCounter){
		speedPI();
		Measured.controlLoop.speedPI_counter = 0;
	}
	currentPI();
}

// Reset the control loop
void controlLoop_reset(){
	Measured.controlLoop.speedPI_output = 0;
	Measured.controlLoop.speedPI_integral = 0;
	Measured.controlLoop.currentPI_output = 0;
	Measured.controlLoop.currentPI_integral = 0;
	Measured.controlLoop.speedPI_counter = 0;
}

