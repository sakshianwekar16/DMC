/*
 * SVM.h
 *
 *  Created on: Oct 7, 2024
 *      Author: pc
 */

#ifndef HEADERFILE_SVM_H_
#define HEADERFILE_SVM_H_

void SVMRun(int16_t volts, uint16_t angle);
void updatePWM(int angle,unsigned int half_t0,unsigned int t1,unsigned int t2 );
//unsigned int PDC1Latch, PDC2Latch, PDC3Latch;

#endif /* HEADERFILE_SVM_H_ */
