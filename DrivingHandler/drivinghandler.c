// brake.c
#include <stdio.h> 
#include <stdint.h>
#include"brake.h"
#include"measurement.h"
#include"sharedData.h"
#include"initialconfig.h"
#include"taskhandler.h"
#include"cruisecontrol.h"
#include"pedalAssist.h"
//FIXED_VALS_t Fixedvalue;
//MEASURED_t Measured;


//uint32_t update_rpm_based_on_brake_status(uint32_t brake){
//    if (brake == 0 ) {
//        // If brake is applied, set RPM to minimum
//    	Display.out.brake = 0x20;
//        return 0;
//    } else {
////       return Measured.throttle.calculated;
//    	Display.out.brake = 0x00;
////    	return PedalAssist.targetRPM;
//    }
//}

//void checkBrake(void){
//	if (0 == HAL_GPIO_ReadPin(BRAKE_GPIO_Port, BRAKE_Pin)){
//		Display.out.brake = 0x20;
//		ControlVals.brakeStatus = 1;
//	} else {
//		Display.out.brake = 0x00;
//		ControlVals.brakeStatus = 0;
//	}
//}


void handleDrivingInputSource(void){
//    update_rpm_based_on_brake_status(Measured.brakeRaw);
	pedal_handle();
	calculate_throttle(Measured.throttle.raw,FixedValue.max_rpm);

	if (Measured.brakeRaw == 0){
		Display.out.brake = 0x20;
		Measured.TargetRPM = 0;
//		cruise_stop();
	} else {
		Display.out.brake = 0x00;
		uint32_t th = Measured.throttle.calculated;
//		uint32_t cs = CruiseMode.speed;
		uint32_t cs = 0;
		uint32_t pas = PedalAssist.targetRPM;
		uint32_t trpm = 0;

		// Decide the input source
		if (pas > th && pas > cs){
			// Running on pedal assist
			trpm = pas;
//			cruise_stop();
		} else {
			// running on throttle or cruise mode
			if (th > cs){
				// Not sure if cruise should be reset here or not as redundancy
				trpm = th;
			} else if (th <= cs){
				trpm = cs;
			} else {
				// program should not reach here. if it comes here by any bug, then reset speed.
				trpm = 0;
			}
		}

		// checking if the target rpm is in valid range
		if (trpm < 0){
			// program should not reach here.
			Measured.TargetRPM = 0;
		} else if (trpm > FixedValue.maxRPMLimit){
			Measured.TargetRPM = FixedValue.maxRPMLimit;
		} else {
			Measured.TargetRPM= trpm;
		}

     }
}



