/*
 * controlLoop.h
 *
 *  Created on: Oct 8, 2024
 *      Author: pc
 */

#ifndef HEADERFILE_CONTROLLOOP_H_
#define HEADERFILE_CONTROLLOOP_H_

void speedPI();
void currentPI();
void controlLoop_run();
void controlLoop_reset();
void updateSpeedPIValues(void);


#endif /* HEADERFILE_CONTROLLOOP_H_ */
