/*
 * cruisecontrol.h
 *
 *  Created on: Oct 11, 2024
 *      Author: pc
 */
#include"stdint.h"
#ifndef HEADERFILE_CRUISECONTROL_H_
#define HEADERFILE_CRUISECONTROL_H_

void update_time(uint32_t time);
void cruise_handle();
void cruise_start();
void cruise_toggle();
void cruise_stop();

#endif /* HEADERFILE_CRUISECONTROL_H_ */
