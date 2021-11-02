/*
 * TIMER1_Program.c
 *
 *  Created on: Sep 27, 2021
 *      Author: Eman
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER1_Private.h"
#include "TIMER1_Config.h"

void (*PReturnFun)(void);
void TIMER1_voidInit(void)
{
//Select mode
//  WGM12 ---> BIT 3 , WGM13 ---> BIT 4	in TCCR1B
//  WGM10 ---> BIT 0 , WGM11 ---> BIT 1	in TCCR1A
#if 	OPERATION_MODE==NORMAL_MODE
	CLR_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);

	// Enable the Overflow interrupt
	SET_BIT(TIMSK,2);

#elif 	OPERATION_MODE==PWM_PHASE_CORRECT_8BIT
	SET_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
#elif 	OPERATION_MODE==PWM_PHASE_CORRECT_9BIT
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
#elif 	OPERATION_MODE==PWM_PHASE_CORRECT_10BIT
	SET_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
#elif 	OPERATION_MODE==CTC_OCR1A

	CLR_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
#elif 	OPERATION_MODE==PWM_FAST_8BIT
	SET_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
#elif 	OPERATION_MODE==PWM_FAST_9BIT
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
#elif 	OPERATION_MODE==PWM_FAST_10BIT
	SET_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
#elif 	OPERATION_MODE==PWM_PHASE_FREQUENCY_CORRECT_ICR1
	CLR_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
#elif 	OPERATION_MODE==PWM_PHASE_FREQUENCY_CORRECT_OCR1A
	SET_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
#elif 	OPERATION_MODE==PWM_PHASE_CORRECT_ICR1
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
#elif 	OPERATION_MODE==PWM_PHASE_CORRECT_OCR1A
	SET_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	CLR_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
#elif 	OPERATION_MODE==CTC_ICR1
	CLR_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
#elif 	OPERATION_MODE==RESERVED
	SET_BIT(TCCR1A,0);
	CLR_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
#elif 	OPERATION_MODE==FAST_PWM_ICR1
	CLR_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
#elif 	OPERATION_MODE==FAST_PWM_OCR1A
	SET_BIT(TCCR1A,0);
	SET_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	SET_BIT(TCCR1B,4);
#endif


#if CHANNEL_MODE==CHANNEL_A
	// SElECT COMPARE OUTPUT MODE Channel A
	TCCR1A &= 0b00111111;
	TCCR1A |= (COMPARE_OC1A_MODE<<6);
	// Activate Channel A output compare Interrupt
	SET_BIT(TIMSK,4);

#elif CHANNEL_MODE==CHANNEL_B
	// SELECT COMPARE OUTPUT MODE Channel B
	TCCR1A &= 0b11001111;
	TCCR1A |= (COMPARE_OC1B_MODE<<4);
	// Activate Channel B output compare Interrupt
	SET_BIT(TIMSK,3);
#endif

// we use bit masking to select our prescaler
	TCCR1B &= 0b11111000;
	TCCR1B |= PRESCALER;

}

// Fucntion to set the Input Compare Register
void TIMER1_voidSetICR1Value(u16 Copy_u16ICR1Value)
{
	ICR1= Copy_u16ICR1Value;
}

// Function to set the Output Compare Register
void TIMER1_voidSetOCR1AValue(u16 Copy_u16OCR1AValue)
{
	OCR1A= Copy_u16OCR1AValue;
}

void TIMER1_voidCallBackFunction(void (*Copy_PReturnFunction)(void))
{
	PReturnFun=Copy_PReturnFunction;
}

/*ISR for Timer1 COMPA*/
void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{
	PReturnFun();
}


