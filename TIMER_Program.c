/*
 * TIMER_Program.c
 *
 *  Created on: 21 Sep 2021
 *      Author: Viro
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER_Private.h"
#include "TIMER_Config.h"


void (*CallBackFun)(void);

void TIMER0_voidInit(void)
{
#if TIMER0_MODE==TIMER0_NORMAL_MODE
	/*SET NORMAL TIMER MODE*/
	CLR_BIT(TCCR0 , 3);
	CLR_BIT(TCCR0 , 6);
	/*OVERFLOAW INTERUPT ENABLE*/
	SET_BIT(TIMSK , 0);

#elif TIMER0_MODE==TIMER0_CTC_MODE
	/*SET CTC TIMER MODE*/
	SET_BIT(TCCR0 , 3);
	CLR_BIT(TCCR0 , 6);
	/*OVERFLOAW INTERUPT ENABLE*/
	SET_BIT(TIMSK , 1);
	/*CTC PIN M ODE*/


#elif TIMER0_MODE==TIMER0_PWM_PHASECORRECT_MODE
	/*SET PMW_PHASECORRECT TIMER MODE*/
	CLR_BIT(TCCR0 , 3);
	SET_BIT(TCCR0 , 6);
#elif TIMER0_MODE==TIMER0_PWM_FAST_MODE
	/*SET PMW_PHASECORRECT TIMER MODE*/
	SET_BIT(TCCR0 , 3);
	SET_BIT(TCCR0 , 6);
#else
#error "You have error in set TIMER0 MODE"
#endif
/*SET PRESCALER*/
	TCCR0 &=TIMER0_BITMASK_PRESCALER;
	TCCR0|=TIMER0_PRESCALER;

#if OC0_PIN_MODE ==OC0_PIN_DISCONNECT
	CLR_BIT(TCCR0 , 5);
	CLR_BIT(TCCR0 , 4);
#elif OC0_PIN_MODE ==OC0_PIN_TOGGLE
	CLR_BIT(TCCR0 , 5);
	SET_BIT(TCCR0 , 4);
#elif OC0_PIN_MODE ==OC0_PIN_CLEAR
	SET_BIT(TCCRO , 5);
	CLR_BIT(TCCRO , 4);
#elif OC0_PIN_MODE ==OC0_PIN_SET
	SET_BIT(TCCRO , 5);
	SET_BIT(TCCRO , 4);
#endif
}

void TIMER0_voidSetPrLoad(u8 Copy_u8Preload)
{
	TCNT0=Copy_u8Preload;
}

void TIMER0_voidSetCTCValue(u8 Copy_u8CTC_Value)
{
	OCR0=Copy_u8CTC_Value;
}

void TIMER0_voidSet_CallBackfunction(void(*Copy_voidP_CallBackFun)(void))
{
CallBackFun = Copy_voidP_CallBackFun;
}

void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	CallBackFun();
}


