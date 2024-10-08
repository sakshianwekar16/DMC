#include <stdint.h>
#include "brake.h"
#include "measurement.h"
#include "initialconfig.h"
#include "sharedData.h"
#include "taskhandler.h"
#include "motor.h"
#include"SVM.h"
#include"define.h"

//uint16_t phaseStates[8][6] = {
//    {0x0000, 1, 0x0000, 1, 0x0000, 1},  // Row 0
//    {0xFFFF, 1, 0x0000, 0, 0x0000, 1},  // Row 1 (AH-BL)
//    {0x0000, 1, 0xFFFF, 1, 0x0000, 0},  // Row 2 (BH-CL)
//    {0xFFFF, 1, 0x0000, 1, 0x0000, 0},  // Row 3 (AH-CL)
//    {0x0000, 0, 0x0000, 1, 0xFFFF, 1},  // Row 4 (CH-AL)
//    {0x0000, 1, 0x0000, 0, 0xFFFF, 1},  // Row 5 (CH-BL)
//    {0x0000, 0, 0xFFFF, 1, 0x0000, 1},  // Row 6 (BH-AL)
//    {0x0000, 1, 0x0000, 1, 0x0000, 1}   // Row 7
//};

// Function to get PWM value for phase A based on its state
int32_t get_PHASEA_PWM_Value() {

    if (Measured.hallPosition == 1 || Measured.hallPosition == 3) {

        Measured.PhaseA = Measured.TargetRPM;
         return Measured.PhaseA;// Return RPM if phase A is high
    }

    else if (Measured.hallPosition == 4 || Measured.hallPosition == 6) {

        Measured.PhaseA = 0;
         return Measured.PhaseA;// Return RPM if phase A is high
    }
    else{
    	Measured.PhaseA = -1;
    	return Measured.PhaseA;
    }
}

// Function to get PWM value for phase B
int32_t get_PHASEB_PWM_Value() {

    if (Measured.hallPosition == 2 || Measured.hallPosition  == 6) {
    	 Measured.PhaseB = Measured.TargetRPM;
        return  Measured.PhaseB;// Return RPM if phase B is high
    }
    else if (Measured.hallPosition == 1 || Measured.hallPosition == 5){
    	Measured.PhaseB = 0;
    	return Measured.PhaseB;
    }
    else {
    	Measured.PhaseB = -1;
    	return Measured.PhaseB;// Return 0 if phase B is low
    }
}

// Function to get PWM value for phase C
int32_t get_PHASEC_PWM_Value() {

    if (Measured.hallPosition == 4 || Measured.hallPosition == 5) {
    	 Measured.PhaseC= Measured.TargetRPM;
        return  Measured.PhaseC;// Return RPM if phase C is high
    }
    else if (Measured.hallPosition == 2 || Measured.hallPosition == 3) {
       	 Measured.PhaseC = 0;
           return  Measured.PhaseC;// Return RPM if phase C is high
       }
    else{
    	Measured.PhaseC = -1;
    	return Measured.PhaseC;// Return 0 if phase C is low
    }
}

void phaseAdv_updateAngle(void){
	if (Measured.motorSpeed.speed <= Fixedvalue.phaseAdv_baseSpeed){
		float linearAdv = ((float)Measured.motorSpeed.speed / (float)Fixedvalue.phaseAdv_baseSpeed) * (float)Fixedvalue.phaseAdv_maxAngle;
		Fixedvalue.phaseAdv.advanceAngle = (linearAdv > Fixedvalue.phaseAdv_maxAngle)? Fixedvalue.phaseAdv_maxAngle : linearAdv;
	} else {
		Fixedvalue.phaseAdv.advanceAngle = Fixedvalue.phaseAdv_maxAngle;
	}
}

void motor_sineCommutation(void){

//	if (ControlVals.targetRPM > 0){
//		if (checkStall() != 0){
////			Motor.faults.stall = 1;
//			ProtectionVals.faults.stall = 1;
//			Display.out.errorCode8.motor = 1;
//		}
//	}
//
//	TestVals.sineComCalled++;
//	TestVals.comStarted++;
//	controlLoop_run();

	uint16_t period = Measured.motorPeriod.period;

	if (period != 0){
		Fixedvalue.phaseInc = ((uint32_t) PHASE_INC_CALC / (uint32_t) period);
	} else {
		// Add some handling for zero period here
	}
//	Fixedvalue.phaseIncAcc += Fixedvalue.phaseInc;
//	if (Fixedvalue.phaseIncAcc >= 10923){
//		Fixedvalue.phaseIncAcc = 10923;
//	}
//	else{
		if (Fixedvalue.invertMotor == 1){
			if(Fixedvalue.runDirectionFlag == REVERSE){
				Fixedvalue.phase -= Fixedvalue.phaseInc;
			}else{
				Fixedvalue.phase += Fixedvalue.phaseInc;
			}
		} else {
			if(Fixedvalue.runDirectionFlag == REVERSE){
				Fixedvalue.phase += Fixedvalue.phaseInc;
			}else{
				Fixedvalue.phase -= Fixedvalue.phaseInc;
			}
		}

//	}
//	MotorRun.phaseIncAcc += MotorRun.phaseInc;
//	if (MotorRun.phaseIncAcc < 10922x){
//		MotorRun.phase -= MotorRun.phaseInc; //motovolt
//		MotorRun.phase += MotorRun.phaseInc; //aurita
//	} else {
//		motorRun.phase = W
//	}


	Fixedvalue.volts = Measured.TargetRPM * 4;

	SVMRun(Fixedvalue.volts, Fixedvalue.phase);
//	TestVals.comCompleted++;
//	SVMRun(controlVals.targetRPM, motorRun.phase);
}






