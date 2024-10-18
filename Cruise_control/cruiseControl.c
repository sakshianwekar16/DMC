/*
 * cruiseControl.c
 *
 *  Created on: Oct 11, 2024
 *      Author: pc
 */

#include "cruiseControl.h"
#include "sharedData.h"
CRUISE_MODE_t CruiseMode;

void update_time(uint32_t time){
	CruiseMode.throttleBaseValueSetTime = time;
	CruiseMode.t = time;
}
void setBaseThrottleValue(uint16_t th){
	CruiseMode.throttleBaseValue = (int16_t)th;
//	CruiseMode.throttleBaseValueSetTime = msec;
}

void checkThrottlePosition(){
	int16_t th = Measured.throttle.calculated;
	int16_t delta = CruiseMode.throttleBaseValue - th;

	if (delta > CruiseMode.throttleMoveThreshold){		// for downward movement detection
		setBaseThrottleValue(th);
	} else if (delta < -CruiseMode.throttleMoveThreshold){	// for upward movement detection
		setBaseThrottleValue(th);
		cruise_stop();
	} else {
		// Do nothing
	}
}

void cruise_start(){
//	if (CruiseMode.throttleBaseValue >= CruiseMode.cruiseSetBaseValue){		// this line could be replaced by motor speed variable, but to reduce number of dependencies, throttle is used
	if (Measured.motorSpeed.speed >= CruiseMode.cruiseSetBaseValue){
		CruiseMode.flags.isCruising = 1U;
		Display.out.errorCode8.cruise = 1U;
		CruiseMode.speed = CruiseMode.throttleBaseValue;
	}
}

void cruise_stop(){
	CruiseMode.flags.isCruising = 0U;
	Display.out.errorCode8.cruise = 0U;
	CruiseMode.speed = 0;
}
void cruise_toggle(){
	if (0U == CruiseMode.flags.isCruising){
		cruise_start();
	} else if (1U == CruiseMode.flags.isCruising){
		cruise_stop();
	} else {
		// Do nothing
	}
}

void setAutoCruiseIfThrottleStable(){
	if(0U == CruiseMode.flags.isCruising){
		if (CruiseMode.throttleBaseValueSetTime + CruiseMode.timeToSetAutoCruise < CruiseMode.t){
			cruise_start();
		}
	}
}

void checkManualCruise(){
	if (CruiseMode.flags.displayManualCriuseLastState != Display.in.parsed.multiParam.manualCruise){
		cruise_toggle();
		CruiseMode.flags.displayManualCriuseLastState = Display.in.parsed.multiParam.manualCruise;
	}
}

void cruise_handle(){
	checkThrottlePosition();
//	setAutoCruiseIfThrottleStable();	// Comment this line to disable auto cruise
//	checkManualCruise();				// Comment this line to disable manual cruise
}

