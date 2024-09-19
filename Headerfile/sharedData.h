/*
 * sharedData.h
 *
 *  Created on: Sep 19, 2024
 *      Author: Admin
 */

#ifndef HEADERFILE_SHAREDDATA_H_
#define HEADERFILE_SHAREDDATA_H_

typedef struct {
	uint16_t raw;
	uint16_t filtered;
	int32_t calculated;
} ADC_DATA_t;

typedef struct {
	ADC_DATA_t current, voltage, throttle;
	uint8_t brakeRaw, brake;
	uint8_t hallPosition;
} MEASURED_t;
extern MEASURED_T Measured;

typedef struct {
	union {
		struct{
			uint16_t hallInvalid : 1;
			uint16_t stall : 1;
			uint16_t throttle : 1;
			uint16_t : 1;
			uint16_t underVolt : 1;
			uint16_t overVolt : 1;
			uint16_t : 1;
			uint16_t overCurrent : 1;
			uint16_t : 1;
			uint16_t overTemperature : 1;
			uint16_t : 1;
			uint16_t : 1;
			uint16_t : 1;
			uint16_t : 1;
			uint16_t : 1;
			uint16_t : 1;
		};
		uint16_t value;
	} faults;
} PROTECTION_t;
extern PROTECTION_t Protection;

#endif /* HEADERFILE_SHAREDDATA_H_ */
