/*
 * TIMER1_Private.h
 *
 *  Created on: Sep 27, 2021
 *      Author: Eman
 */

#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_

#define TCCR1A	*((volatile u8*)0x4F)
#define TCCR1B	*((volatile u8*)0x4E)
#define TCNT1	*((volatile u16*)0x4C)
#define OCR1A	*((volatile u16*)0x4A)
#define OCR1B	*((volatile u16*)0x48)
#define ICR1	*((volatile u16*)0x46)
#define TIMSK	*((volatile u16*)0x59)

// OPERATION MODDES
 #define NORMAL_MODE							0
 #define PWM_PHASE_CORRECT_8BIT					1
 #define PWM_PHASE_CORRECT_9BIT					2
 #define PWM_PHASE_CORRECT_10BIT				3
 #define CTC_OCR1A								4
 #define PWM_FAST_8BIT							5
 #define PWM_FAST_9BIT							6
 #define PWM_FAST_10BIT							7
 #define PWM_PHASE_FREQUENCY_CORRECT_ICR1		8
 #define PWM_PHASE_FREQUENCY_CORRECT_OCR1A		9
 #define PWM_PHASE_CORRECT_ICR1					10
 #define PWM_PHASE_CORRECT_OCR1A				11
 #define CTC_ICR1								12
 #define RESERVED								13
 #define FAST_PWM_ICR1							14
 #define FAST_PWM_OCR1A							15

// CHANNELS
#define CHANNEL_A	0
#define CHANNEL_B	1


// COMPARE OC1A/OC1B modes
#define NORMAL_PORT_OPERATION	0
#define TOGGLE_PIN				1
#define CLR_PIN					2
#define SET_PIN					3

// FAST PWM OC1A/OC1B modes & PHASE CORRECT PWM OC1A/OC1B modes
#define NORMAL_PORT_OPERATION	0
#define TOGGLE_MODE				1
#define CLEAR_MODE				2
#define SET_MODE				3

//PRESCALER MODES
#define NO_CLOCK_SOURCE				0
#define NO_PRESCALING				1
#define PRESCALER_8					2
#define PRESCALER_64				3
#define PRESCALER_256				4
#define PRESCALER_1024				5
#define EXT_CLOCK_FALLING_EDGE		6
#define EXT_CLOCK_RISING_EDGE		7


#endif /* TIMER1_PRIVATE_H_ */
