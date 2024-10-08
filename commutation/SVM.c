/*
 * SVM.c
 *
 *  Created on: Oct 7, 2024
 *      Author: pc
 */

#include "stdint.h"
#include "tim.h"
#include "SVM.h"
#include"sharedData.h"

// shifting these defines to a global file would be a nice idea
#define	VECTOR1	0				// 0 degrees
#define	VECTOR2	0x2aaa			// 60 degrees
#define	VECTOR3	0x5555			// 120 degrees
#define	VECTOR4	0x8000			// 180 degrees
#define	VECTOR5	0xaaaa			// 240 degrees
#define	VECTOR6	0xd555			// 300 degrees
#define	SIXTY_DEG	0x2aaa

#define LOOPTIME_MICROSEC 		50
#define SYSTEM_CLOCK_MHZ 		64U
#define LOOPTIME_SVM			(uint16_t)(((LOOPTIME_MICROSEC*SYSTEM_CLOCK_MHZ))-1)

#define VOLTS_LIMIT 28377

// this near is ignored, need to see why it is used
int __attribute__ ((near)) sinetable[172] = { 0, 201, 401, 602, 803, 1003, 1204,
		1404, 1605, 1805, 2005, 2206, 2406, 2606, 2806, 3006, 3205, 3405, 3605,
		3804, 4003, 4202, 4401, 4600, 4799, 4997, 5195, 5393, 5591, 5789, 5986,
		6183, 6380, 6577, 6773, 6970, 7166, 7361, 7557, 7752, 7947, 8141, 8335,
		8529, 8723, 8916, 9109, 9302, 9494, 9686, 9877, 10068, 10259, 10449,
		10639, 10829, 11018, 11207, 11395, 11583, 11771, 11958, 12144, 12331,
		12516, 12701, 12886, 13070, 13254, 13437, 13620, 13802, 13984, 14165,
		14346, 14526, 14706, 14885, 15063, 15241, 15419, 15595, 15772, 15947,
		16122, 16297, 16470, 16643, 16816, 16988, 17159, 17330, 17500, 17669,
		17838, 18006, 18173, 18340, 18506, 18671, 18835, 18999, 19162, 19325,
		19487, 19647, 19808, 19967, 20126, 20284, 20441, 20598, 20753, 20908,
		21062, 21216, 21368, 21520, 21671, 21821, 21970, 22119, 22266, 22413,
		22559, 22704, 22848, 22992, 23134, 23276, 23417, 23557, 23696, 23834,
		23971, 24107, 24243, 24377, 24511, 24644, 24776, 24906, 25036, 25165,
		25293, 25420, 25547, 25672, 25796, 25919, 26042, 26163, 26283, 26403,
		26521, 26638, 26755, 26870, 26984, 27098, 27210, 27321, 27431, 27541,
		27649, 27756, 27862, 27967, 28071, 28174, 28276, 28377 };

int getvector(int angle) {
	int retval;
	if (angle < 0x8000) {
		if (angle < 0x5555) {
			if (angle < 0x2aaa) {
				retval = 0;
			} else {
				retval = 0x2aaa;
			}
		} else {
			retval = 0x5555;
		}
	} else {
		if (angle < 0xd555) {
			if (angle < 0xaaaa) {
				retval = 0x8000;
			} else {
				retval = 0xaaaa;
			}
		} else {
			retval = 0xd555;
		}
	}
	return retval;
}

void SVMRun(int16_t volts, uint16_t angle) {
	// These variables hold the normalized sector angles used to find
	// t1, t2.
	uint16_t vector;
	unsigned int angle1, angle2;

	// These variables hold the space vector times.
	unsigned int half_t0, t1, t2, tpwm, voltstpwm;

	// Calculate the total PWM count period
	tpwm = LOOPTIME_SVM;

	// Limit volts input to avoid overmodulation.
	if (volts > VOLTS_LIMIT)
		volts = VOLTS_LIMIT;

	vector = getvector(angle);

	angle2 = angle - vector;

	angle1 = SIXTY_DEG - angle2;

	t1 = sinetable[(unsigned char) (angle1 >> 6)];
	t2 = sinetable[(unsigned char) (angle2 >> 6)];

	voltstpwm = (int) ((volts * tpwm) >> 15);
	t1 = (int) ((t1 * voltstpwm) >> 15);
	t2 = (int) ((t2 * voltstpwm) >> 15);
	half_t0 = (tpwm - t1 - t2) >> 1;

	updatePWM(angle, half_t0, t1, t2);
}

void updatePWM(int angle, unsigned int half_t0, unsigned int t1,
		unsigned int t2) {
//	unsigned int PDC1Latch, PDC2Latch, PDC3Latch;
	if (angle < 0x8000) {
		if (angle < 0x5555) {
			if (angle < 0x2aaa) {
				Fixedvalue.PDC1Latch = t1 + t2 + half_t0;
				Fixedvalue.PDC2Latch = t2 + half_t0;
				Fixedvalue.PDC3Latch = half_t0;
			} else {
				Fixedvalue.PDC1Latch = t1 + half_t0;
				Fixedvalue.PDC2Latch = t1 + t2 + half_t0;
				Fixedvalue.PDC3Latch = half_t0;
			}
		} else {
			Fixedvalue.PDC1Latch = half_t0;
			Fixedvalue.PDC2Latch = t1 + t2 + half_t0;
			Fixedvalue.PDC3Latch = t2 + half_t0;
		}
	} else {
		if (angle < 0xd555) {
			if (angle < 0xaaaa) {
				Fixedvalue.PDC1Latch = half_t0;
				Fixedvalue.PDC2Latch = t1 + half_t0;
				Fixedvalue.PDC3Latch = t1 + t2 + half_t0;
			} else {
				Fixedvalue.PDC1Latch = t2 + half_t0;
				Fixedvalue.PDC2Latch = half_t0;
				Fixedvalue.PDC3Latch = t1 + t2 + half_t0;
			}
		} else {
			Fixedvalue.PDC1Latch = t1 + t2 + half_t0;
			Fixedvalue.PDC2Latch = half_t0;
			Fixedvalue.PDC3Latch = t1 + half_t0;
		}
	}
//	 Dutycycle1 =PDC1Latch;
//	 Dutycycle2 =PDC2Latch;
//	 Dutycycle3 =PDC3Latch;
//	TIM1->CCR3 = PDC1Latch;
//	TIM1->CCR2 = PDC3Latch;
//	TIM1->CCR1 = PDC2Latch;
}



