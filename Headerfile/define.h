

#ifndef INC_DEFINES_H_
#define INC_DEFINES_H_

#define PHASE_ZERO 	0
#define PHASE_ONE	((PHASE_ZERO + 65536/6) % 65536) //10922
#define PHASE_TWO	((PHASE_ONE + 65536/6) % 65536)  //21845
#define PHASE_THREE	((PHASE_TWO + 65536/6) % 65536)  //32768
#define PHASE_FOUR	((PHASE_THREE + 65536/6) % 65536)//43691
#define PHASE_FIVE	((PHASE_FOUR + 65536/6) % 65536) //54613
#define HALL_60 	(int16_t)(65536 / 6)

#define MOTOR_RPM_TYRE 			200
#define GEAR_RATIO 				4.5

#define SYSTEM_CLOCK 			64000000UL
#define TIMER_PRESCALER 		146
#define MIN_MOTOR_SPD 			10
#define MAX_MOTOR_SPD 			(MOTOR_RPM_TYRE*GEAR_RATIO) //should be in RPM
#define MOTOR_POLEPAIRS 		10
#define PWM_FREQUENCY_HZ 		20000

#define MAX_HALL_PERIOD			(unsigned long)(((float)SYSTEM_CLOCK / (float)TIMER_PRESCALER) / (float)((MIN_MOTOR_SPD * MOTOR_POLEPAIRS)/10))
#define MIN_HALL_PERIOD			(unsigned long)(((float)SYSTEM_CLOCK / (float)TIMER_PRESCALER) / (float)((MAX_MOTOR_SPD * MOTOR_POLEPAIRS)/10))


// For motor speed
#define SPEED_MULTI     (unsigned long)(((float)SYSTEM_CLOCK/(float)(TIMER_PRESCALER*MOTOR_POLEPAIRS))*(float)60)

#define PHASE_INC_CALC			(unsigned long)((float)SYSTEM_CLOCK/((float)(TIMER_PRESCALER)*(float)(PWM_FREQUENCY_HZ))*(float)(65536/6))


// For display
#define DISPLAY_RX_SIZE 20
#define DISPLAY_RECONNECT_TIMEOUT 5000
#endif /* INC_DEFINES_H_ */

