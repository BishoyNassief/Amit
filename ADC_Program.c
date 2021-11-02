/*
 * ADC_Program.c
 *
 *  Created on: Sep 19, 2021
 *      Author: gerges
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include "ADC_Interface.h"
#include"ADC_Private.h"
#include <util/delay.h>

void (*PtrToFun_ADC)(void);

void ADC_voidInit(void)
{
	/*1-Select Reference Voltage-->  (AVCC)*/
	SET_BIT(ADMUX,6);
	CLR_BIT(ADMUX,7);
	/*2- Select Left or Right Adjust--> (RIGHT Adjust) */
	CLR_BIT(ADMUX,5);
	/*3- Select Prescaler (128)*/
	SET_BIT(ADCSRA,2);
	SET_BIT(ADCSRA,1);
	SET_BIT(ADCSRA,0);
	/*4- ADC Enable*/
	SET_BIT(ADCSRA,7);
}
u16 ADC_u16StartConversion(u8 Copy_u8Channel)
{
	u16 LOC_u16DataValue=0;
	/*Mask the 5 MSB IN the data */
	Copy_u8Channel&=0x07;
	/*MASK The 5 LSB In ADMUX Register */
	ADMUX&=0xE0;
	/*Set your channel*/
	ADMUX|=Copy_u8Channel;
	/*Start Conversion*/
	SET_BIT(ADCSRA,6);
	/*wait ADC Flag until ADC End conversion*/
	while(GET_BIT(ADCSRA,4)==0);
	//LOC_u16DataValue=ADCL|(ADCH<<8);
	LOC_u16DataValue=ADC;
	return LOC_u16DataValue;
}
void ADC_voidInit_Interrupt(void)
{
	/*1-Select Reference Voltage-->  (AVCC)*/
	SET_BIT(ADMUX,6);
	CLR_BIT(ADMUX,7);
	/*2- Select Left or Right Adjust--> (RIGHT Adjust) */
	CLR_BIT(ADMUX,5);
	/*3- Select Prescaler (128)*/
	SET_BIT(ADCSRA,2);
	SET_BIT(ADCSRA,1);
	SET_BIT(ADCSRA,0);
	/*4- ADC Enable*/
	SET_BIT(ADCSRA,7);
	/*ADC Interrupt Enable*/
	SET_BIT(ADCSRA,3);
}
void ADC_u16StartConversion_Interrupt(u8 Copy_u8Channel)
{
	/*Mask the 5 MSB IN the data */
	Copy_u8Channel&=0x07;
	/*MASK The 5 LSB In ADMUX Register */
	ADMUX&=0xE0;
	/*Set your channel*/
	ADMUX|=Copy_u8Channel;
	/*Start Conversion*/
	SET_BIT(ADCSRA,6);
	_delay_ms(5);
}
u16 ADC_u16DigitalRead(void)
{
	return ADC;
}

void ADC_voidCallBackFunction(void (*Copy_PtrToFun)(void))
{
	PtrToFun_ADC=Copy_PtrToFun;
}




void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	PtrToFun_ADC();
}
