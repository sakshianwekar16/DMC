/*
 * pedalAssist.h
 *
 *  Created on: Oct 9, 2024
 *      Author: pc
 */

#ifndef HEADERFILE_PEDALASSIST_H_
#define HEADERFILE_PEDALASSIST_H_

//void update_getTick(uint32_t time);
void pedal_riseIntHandler();
void pedal_handle();
void pedal_setLimits(void);

#endif /* HEADERFILE_PEDALASSIST_H_ */
