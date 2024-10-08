// brake.c
#include <stdio.h> 
#include <stdint.h>
#include"brake.h"
#include"measurement.h"
#include"sharedData.h"
#include"initialconfig.h"
#include"taskhandler.h"
//FIXED_VALS_t Fixedvalue;
//MEASURED_t Measured;


uint32_t update_rpm_based_on_brake_status(uint32_t brake) {

    if (brake == 1 ) {
        // If brake is applied, set RPM to minimum
        return 0;
    } else {

        return Measured.throttle.calculated;
    }
}

//void GetDirectionStatus(void){
//	Fixedvalue.runDirectionFlag = FORWARD;
//	return;
//	uint8_t PinStatus = HAL_GPIO_ReadPin(F_R_GPIO_Port, F_R_Pin);
//	if(PinStatus == 0){
//		Fixedvalue.runDirectionFlag = REVERSE;
//	}else{
//		Fixedvalue.runDirectionFlag =  FORWARD;
//	}
//}

