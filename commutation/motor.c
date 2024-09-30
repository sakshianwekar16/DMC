#include <stdint.h>
#include "brake.h"
#include "measurement.h"
#include "initialconfig.h"
#include "sharedData.h"
#include "taskhandler.h"
#include "motor.h"

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
int get_PHASEA_PWM_Value() {

    if (Measured.hallPosition == 1 || Measured.hallPosition == 3) {

        Measured.PhaseA = Measured.TargetRPM;
         return Measured.PhaseA;// Return RPM if phase A is high
    }

    else if (Measured.hallPosition == 4 || Measured.hallPosition == 6) {

        Measured.PhaseA = 0;
         return Measured.PhaseA;// Return RPM if phase A is high
    }
    return -1;
}

// Function to get PWM value for phase B
int get_PHASEB_PWM_Value() {

    if (Measured.hallPosition == 2 || Measured.hallPosition  == 6) {
    	 Measured.PhaseB = Measured.TargetRPM;
        return  Measured.PhaseB;// Return RPM if phase B is high
    }
    else if (Measured.hallPosition == 1 || Measured.hallPosition == 5){
    	Measured.PhaseB = 0;
    	return Measured.PhaseB;
    }
    return -1;  // Return 0 if phase B is low
}

// Function to get PWM value for phase C
int get_PHASEC_PWM_Value() {

    if (Measured.hallPosition == 4 || Measured.hallPosition == 5) {
    	 Measured.PhaseC= Measured.TargetRPM;
        return  Measured.PhaseC;// Return RPM if phase C is high
    }
    else if (Measured.hallPosition == 2 || Measured.hallPosition == 3) {
       	 Measured.PhaseC = 0;
           return  Measured.PhaseC;// Return RPM if phase C is high
       }
    return -1;  // Return 0 if phase C is low
}







