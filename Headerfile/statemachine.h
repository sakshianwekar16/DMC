/*
 * statemachine.h
 *
 *  Created on: Oct 3, 2024
 *      Author: pc
 */

#ifndef HEADERFILE_STATEMACHINE_H_
#define HEADERFILE_STATEMACHINE_H_

void stateMachine_handle(void);

void stateMachine_stepIntoIdle(void);
void stateMachine_stepIntoRun(void);
void stateMachine_stepIntoError(void);


#endif /* HEADERFILE_STATEMACHINE_H_ */
