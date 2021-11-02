/*
 * TIMER1_Config.h
 *
 *  Created on: Sep 27, 2021
 *      Author: Eman
 */

#ifndef TIMER1_CONFIG_H_
#define TIMER1_CONFIG_H_

/* OPERATION MODES
 * -----------------------------------------------------------------------
 *  0- NORMAL_MODE
 *  1- PWM_PHASE_CORRECT_8BIT
 *  2- PWM_PHASE_CORRECT_9BIT
 *  3- PWM_PHASE_CORRECT_10BIT
 *  4- CTC_OCR1A
 *  5- PWM_FAST_8BIT
 *  6- PWM_FAST_9BIT
 *  7- PWM_FAST_10BIT
 *  8- PWM_PHASE_FREQUENCY_CORRECT_ICR1
 *  9- PWM_PHASE_FREQUENCY_CORRECT_OCR1A
 * 10- PWM_PHASE_CORRECT_ICR1
 * 11- PWM_PHASE_CORRECT_OCR1A
 * 12- CTC_ICR1
 * 13- RESERVED
 * 14- FAST_PWM_ICR1
 * 15- FAST_PWM_OCR1A
 * -----------------------------------------------------------------------
 */

#define OPERATION_MODE CTC_OCR1A


/*	COMPARE MODE OC1A/OC1B modes & Fast PWM OC1A/OC1B modes & PHASE CORRECT PWM OC1A/OC1B modes
 * NORMAL_PORT_OPERATION   	 ---> OC1A/OC1B are disconnected
 * TOGGLE_PIN				 ---> Toggle OC1A on Compare match OC1B is disconnected
 * CLR_PIN	  				 ---> Non-Inverting mode
 * SET_PIN					 ---> Inverting mode
 */

/* CHANNEL MODES
 * CHANNEL_A
 * CHANNEL_B
 */
#define CHANNEL_MODE	CHANNEL_A

#define COMPARE_OC1A_MODE	TOGGLE_PIN
#define COMPARE_OC1B_MODE	TOGGLE_PIN

/*	CLOCK MODES
 * NO_CLOCK_SOURCE
 * NO_PRESCALING
 * PRESCALER_8
 * PRESCALER_64
 * PRESCALER_256
 * PRESCALER_1024
 * EXT_CLOCK_FALLING_EDGE
 * EXT_CLOCK_RISING_EDGE
 */
#define PRESCALER PRESCALER_1024


#endif /* TIMER1_CONFIG_H_ */
