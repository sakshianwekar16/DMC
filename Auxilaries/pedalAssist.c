/*
 * pedalAssist.c
 *
 *  Created on: Oct 9, 2024
 *      Author: pc
 */
#include"sharedData.h"
#include"pedalAssist.h"
#include"initialconfig.h"
#include"cruisecontrol.h"
PEDAL_ASSIST_t PedalAssist;

void pedal_riseIntHandler( uint32_t msec){
	uint32_t tick = msec;
	PedalAssist.diff = tick - PedalAssist.lastTick;

	if (PedalAssist.diff > PedalAssist.maxDiff){
		PedalAssist.diff = PedalAssist.maxDiff;
	}
	if (PedalAssist.diff < PedalAssist.minDiff){
		return;
	}
	PedalAssist.lastTick = tick;

	int16_t value = PedalAssist.value + PedalAssist.addAmount;
	if (value > FixedValue.adcResolution){
		value = FixedValue.adcResolution ;
	}
	PedalAssist.value = value;
}

void pedal_handle( uint32_t tick){

//	pedal_setLimits();
	int32_t pedalValue = PedalAssist.value - ((int32_t)(tick - PedalAssist.lastTick) / PedalAssist.derampFactor);
	if (pedalValue < 0){
		PedalAssist.value = 0;
	} else {
		PedalAssist.value = pedalValue;
	}
	int16_t speed = (PedalAssist.value * PedalAssist.maxRPM) >> PedalAssist.scale;

	if (tick > PedalAssist.lastTick + PedalAssist.timeout){
		speed = 0;
	}
	int32_t filteredSpeed = ((30 * speed) + (34 * PedalAssist.targetRPM)) >> 6;
	if (filteredSpeed > FixedValue.max_rpm){
		PedalAssist.targetRPM = FixedValue.max_rpm;
	} else {
		PedalAssist.targetRPM = filteredSpeed;
	}
}

void pedal_setLimits() {
	PedalAssist.level = Display.in.parsed.pedalAssist;
	switch (PedalAssist.level) {
	case 0:
		PedalAssist.maxRPM = PedalAssist.mode0RPM;
		break;

	case 3:
		PedalAssist.maxRPM = PedalAssist.mode1RPM;
		break;

	case 6:
		PedalAssist.maxRPM = PedalAssist.mode2RPM;
		break;

	case 9:
		PedalAssist.maxRPM = PedalAssist.mode3RPM;
		break;

	case 12:
		PedalAssist.maxRPM = PedalAssist.mode4RPM;
		break;

	case 15:
		PedalAssist.maxRPM = PedalAssist.mode5RPM;
		break;

	default:
		PedalAssist.maxRPM = 0;
		break;
	}

	if (PedalAssist.prevLevel != PedalAssist.level) {
//		cruise_stop();
		PedalAssist.prevLevel = PedalAssist.level;
	}
}
