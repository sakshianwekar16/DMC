/*
 * statemachine.c
 *
 *  Created on: Oct 3, 2024
 *      Author: pc
 */
#include "sharedData.h"
#include "initialconfig.h"
#include "motor.h"
#include "statemachine.h"
#include"controlLoop.h"

void stateMachine_handle(void){

	if (Protection.faults.value != 0){
		stateMachine_stepIntoError();
	}

	switch (ControlVals.stateMachine_state){
	case SMS_INITIAL:
		if (0 == Measured.throttle.calculated && 1 == ControlVals.initialAssignmentsCompleted){
			stateMachine_stepIntoIdle();
		} else {
			/* nothing to do */
		}
		break;

	case SMS_IDLE:
		if (Measured.TargetRPM > 0){
			stateMachine_stepIntoRun();
		} else {
			if(1 == FixedValue.istimerON_A || 1 == FixedValue.islowersideON_A ||1 == FixedValue.istimerON_B || 1 == FixedValue.islowersideON_B ||1 == FixedValue.istimerON_C || 1 == FixedValue.islowersideON_C ){
				motordisable();
			}
		}
		break;

	case SMS_RUN:
		if (Measured.TargetRPM > 0){
			motor_sineCommutation();
//			motor_sixStepCommutation();
		} else {
			stateMachine_stepIntoIdle();
		}
		break;

	case SMS_ERROR:
		if (1 == FixedValue.istimerON_A || 1 == FixedValue.islowersideON_A ||1 == FixedValue.istimerON_B || 1 == FixedValue.islowersideON_B ||1 == FixedValue.istimerON_C || 1 == FixedValue.islowersideON_C ){
			motordisable();
		}
		if (0 == Protection.faults.value){
			if (0 == Measured.throttle.calculated){
				stateMachine_stepIntoIdle();
			}
		} else {
//			error_resetIfSolved();
		}
		break;
	}

}

void stateMachine_stepIntoIdle(void){
//	Fixedvalue.counter = 0;
	controlLoop_reset();
	motordisable();
	ControlVals.stateMachine_state = SMS_IDLE;
}

void stateMachine_stepIntoRun(void){
	// adjustments
//	Measured.motorPeriod.periodBeforeFilter = MAX_HALL_PERIOD;
//	Measured.motorPeriod.period = MAX_HALL_PERIOD;
//	Fixedvalue.counter = 0;
	controlLoop_reset();
	motorenable();
//	stall_reset();
	ControlVals.stateMachine_state = SMS_RUN;
}

void stateMachine_stepIntoError(void){
	ControlVals.stateMachine_state = SMS_ERROR;
}


