/*
 * SEVEN_SEGEMENT_Program.c
 *
 *  Created on: Oct 28, 2021
 *      Author: Bishoy
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_Config.h"
#include "DIO_Interface.h"
#include "DIO_Private.h"
#include "TIMER_Config.h"
#include "SEVEN_SEGMENT_Interface.h"
#include <util/delay.h>
#include "Timer_Interface.h"

#define ENABLED		1
#define DISABLED	0

u8 Blink_Flag=0;
u8 SEVEN_SEGMENT_FLAG=0;
u8 Flag_1=1;
u8 Flag_2=0;
u8 BlinkMode;

u8 Power_State=0;
u8 GLOBAL_u8UnitDigit =0;
u8 GLOBAL_u8TenthDigit =0;

u8 BlinkCount=0;
u32 Blink_No_Interrupts;
u32 BlinkCount2=0;



void SEVEN_SEGMENT_voidEnable (void)
{
	DIO_u8SetPinDirection(DIO_PIN1 ,DIO_PORTA , PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PIN2 ,DIO_PORTA , PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PIN3 ,DIO_PORTA , PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PIN4 ,DIO_PORTA , PIN_OUTPUT);

	DIO_u8SetPinDirection(DIO_PIN0 ,DIO_PORTB , PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PIN1 ,DIO_PORTB , PIN_OUTPUT);

	DIO_u8SetPinDirection(DIO_PIN3 , DIO_PORTB , PIN_OUTPUT);

	TIMER0_voidSet_CallBackfunction(&Timer0_Interrupt_Function);

	TIMER0_voidSetCTCValue(100);
	TIMER0_voidInit();

}

void SEVEN_SEGMENT_voidON (void)
{
	SEVEN_SEGMENT_FLAG=0;
}

void SEVEN_SEGMENT_voidOFF (void)
{
	SEVEN_SEGMENT_FLAG=2;
}


void SEVEN_SEGEMENT_u8SendNumber (u8 Copy_u8Number)
{
		GLOBAL_u8UnitDigit  = ((Copy_u8Number)%10);
		GLOBAL_u8TenthDigit = ((Copy_u8Number)/10);
}

void Timer0_Interrupt_Function(void)
{
	/*This Part is to display number on 7 segment*/
	if(SEVEN_SEGMENT_FLAG==0)
		{
			/* Enable one segment and disable the other one*/
			SET_BIT(PORTB,1);
			CLR_BIT(PORTB,0);

			/* Send Unit digit*/
			PORTA &= 0b11100001;
			PORTA |= (GLOBAL_u8UnitDigit<<1);

			SEVEN_SEGMENT_FLAG=1;
		}
		else if(SEVEN_SEGMENT_FLAG==1)
		{
			/* Enable the other segment */
			SET_BIT(PORTB,0);
			CLR_BIT(PORTB,1);

			/* Send tenth digit*/
			PORTA &= 0b11100001;
			PORTA |= (GLOBAL_u8TenthDigit<<1);

			SEVEN_SEGMENT_FLAG=0;
		}
		else if(SEVEN_SEGMENT_FLAG==2)
		{
			/*turn off the two segments*/
			SET_BIT(PORTB,0);
			SET_BIT(PORTB,1);
		}
		else
		{
			/*Nothing*/
		}

	/*This part is for 7 segment to blink*/
	if(BlinkMode==ENABLED)
	{
		Blink_Flag=ENABLED;

			if(BlinkCount<=65)
			{
			BlinkCount++;
			}
			else
			{
				if(Flag_2==0)
				{
					Flag_2=1;
					SEVEN_SEGMENT_voidOFF();
				}
				else if(Flag_2==1)
				{
					Flag_2=0;
					SEVEN_SEGMENT_voidON();
				}
				else
				{
					//NOTHING
				}
			BlinkCount=0;
			}
	}
	else
	{
		Blink_Flag=DISABLED;

		if(Flag_2==1)
		{
			SEVEN_SEGMENT_voidON();
		}
		else;
	}

	/*This Part is for the blinking duration*/
	if(BlinkCount2 < Blink_No_Interrupts)
	{
		BlinkCount2++;
	}
	else
	{
		BlinkMode = DISABLED;
		BlinkCount2=0;
	}

}

void SEVEN_SEGMENT_voidBlink(u32 Blink_Time_ms)
{
	BlinkMode=ENABLED;
	BlinkCount2=0;
	Blink_No_Interrupts=Blink_Time_ms;
	/*convert blink time to number of ctc interrupts*/
	Blink_No_Interrupts/=7.5F;
}


u8 SEVEN_SEGMENT_GetBlinkingStatus(void)
{
	return Blink_Flag;
}






