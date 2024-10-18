/*
 * SWS.c
 *
 *  Created on: Oct 9, 2024
 *      Author: pc
 */
#include "sharedData.h"
#include "SWS.h"


void SWS_intHandler(uint32_t msec){
	Measured.singleWireSpeed.tk = msec;
	Measured.singleWireSpeed.rawTickDiff = Measured.singleWireSpeed.tk - Measured.singleWireSpeed.lastTick;
	Measured.singleWireSpeed.lastTick = Measured.singleWireSpeed.tk;
}

void SWS_calculateSpeed(uint32_t msec){
	Measured.singleWireSpeed.tk = msec;
	if (Measured.singleWireSpeed.tk > Measured.singleWireSpeed.lastTick + 1000){
		Measured.singleWireSpeed.tickDiff = 0;
	} else {
		Measured.singleWireSpeed.tickDiff = (uint32_t)(Measured.singleWireSpeed.rawTickDiff);
	}
}

