/*
 * DIO_Program.c
 *
 *  Created on: Sep 5, 2021
 *      Author: gerges
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_Interface.h"
#include"DIO_Private.h"

u8 DIO_u8SetPinDirection(u8 Copy_u8PinNumber,u8 Copy_u8PortNumber,u8 Copy_u8PinDirection)
{
	u8 Error_State=OK;
	if((Copy_u8PinNumber<8)&&(Copy_u8PinNumber>=0))
	{
		if(Copy_u8PinDirection==PIN_OUTPUT)
		{
			switch(Copy_u8PortNumber)
			{
			case DIO_PORTA:
				SET_BIT(DDRA,Copy_u8PinNumber);
				break;
			case DIO_PORTB:
				SET_BIT(DDRB,Copy_u8PinNumber);
				break;
			case DIO_PORTC:
				SET_BIT(DDRC,Copy_u8PinNumber);
				break;
			case DIO_PORTD:
				SET_BIT(DDRD,Copy_u8PinNumber);
				break;
			default:
				Error_State=NOK;
				break;
			}

		}
		else if(Copy_u8PinDirection==PIN_INPUT)
		{
			switch(Copy_u8PortNumber)
			{
			case DIO_PORTA:
				CLR_BIT(DDRA,Copy_u8PinNumber);
				break;
			case DIO_PORTB:
				CLR_BIT(DDRB,Copy_u8PinNumber);
				break;
			case DIO_PORTC:
				CLR_BIT(DDRC,Copy_u8PinNumber);
				break;
			case DIO_PORTD:
				CLR_BIT(DDRD,Copy_u8PinNumber);
				break;
			default:
				Error_State=NOK;
				break;
			}

		}
		else
		{
			Error_State=NOK;
		}
	}
	else
	{
		Error_State=NOK;
	}
	return Error_State;
}

u8 DIO_u8SetPinValue(u8 Copy_u8PinNumber,u8 Copy_u8PortNumber,u8 Copy_u8PinValue)
{
	u8 Error_State=OK;
	if((Copy_u8PinNumber<8)&&(Copy_u8PinNumber>=0))
	{
		switch(Copy_u8PortNumber)
		{
		case DIO_PORTA:
			if(Copy_u8PinValue==PIN_HIGH)
			{
				SET_BIT(PORTA,Copy_u8PinNumber);
			}
			else if(Copy_u8PinValue==PIN_LOW)
			{
				CLR_BIT(PORTA,Copy_u8PinNumber);
			}
			else
			{
				Error_State=NOK;
			}
			break;
		case DIO_PORTB:
			if(Copy_u8PinValue==PIN_HIGH)
			{
				SET_BIT(PORTB,Copy_u8PinNumber);
			}
			else if(Copy_u8PinValue==PIN_LOW)
			{
				CLR_BIT(PORTB,Copy_u8PinNumber);
			}
			else
			{
				Error_State=NOK;
			}
			break;
		case DIO_PORTC:
			if(Copy_u8PinValue==PIN_HIGH)
			{
				SET_BIT(PORTC,Copy_u8PinNumber);
			}
			else if(Copy_u8PinValue==PIN_LOW)
			{
				CLR_BIT(PORTC,Copy_u8PinNumber);
			}
			else
			{
				Error_State=NOK;
			}
			break;
		case DIO_PORTD:
			if(Copy_u8PinValue==PIN_HIGH)
			{
				SET_BIT(PORTD,Copy_u8PinNumber);
			}
			else if(Copy_u8PinValue==PIN_LOW)
			{
				CLR_BIT(PORTD,Copy_u8PinNumber);
			}
			else
			{
				Error_State=NOK;
			}
			break;
		default:
			Error_State=NOK;
			break;
		}
	}
	else
	{
		Error_State=NOK;
	}
	return Error_State;
}

/*u8 DIO_u8GetPinValue(u8 Copy_u8PinNumber,u8 Copy_u8PortNumber,u8* Copy_u8PinValue);
u8 DIO_u8TogglePinValue(u8 Copy_u8PinNumber,u8 Copy_u8PortNumber);

u8 DIO_u8SetPortDirection(u8 Copy_u8PortNumber,u8 Copy_u8PinDirection);
u8 DIO_u8SetPortValue(u8 Copy_u8PortNumber,u8 Copy_u8PinValue);*/

void DIO_u8SetPortValue(u8 Copy_u8PortNumber,u8 Copy_u8PortValue)
{
	switch(Copy_u8PortNumber)
	{
	case DIO_PORTA :PORTA =  Copy_u8PortValue ;break;
	case DIO_PORTB : PORTB =  Copy_u8PortValue ;break;
	case DIO_PORTC : PORTC =  Copy_u8PortValue ;break;
	case DIO_PORTD : PORTD =  Copy_u8PortValue ;break;
	}

}
void DIO_u8SetPortDirection(u8 Copy_u8PortNumber,u8 Copy_u8PortDirection)
{
	switch(Copy_u8PortNumber)
	{
	case DIO_PORTA : DDRA =  Copy_u8PortDirection ;break;
	case DIO_PORTB : DDRB =  Copy_u8PortDirection ;break;
	case DIO_PORTC : DDRC =  Copy_u8PortDirection ;break;
	case DIO_PORTD : DDRD =  Copy_u8PortDirection ;break;
	}

}

u8 DIO_u8GetPinValue(u8 Copy_u8PinNumber,u8 Copy_u8PortNumber,u8* Copy_u8PinValue)
{
	u8 ErrorState=OK;
	if(Copy_u8PinNumber<8)
	{
		switch(Copy_u8PortNumber)
		{
		case DIO_PORTA :
			*Copy_u8PinValue=GET_BIT(PINA,Copy_u8PinNumber);
			break;
		case DIO_PORTB :
			*Copy_u8PinValue=GET_BIT(PINB,Copy_u8PinNumber);
			break;
		case DIO_PORTC :
			*Copy_u8PinValue=GET_BIT(PINC,Copy_u8PinNumber);
			break;
		case DIO_PORTD :
			*Copy_u8PinValue=GET_BIT(PIND,Copy_u8PinNumber);
			break;
		default:
			ErrorState=NOK;
			break;
		}
	}
	else
	{
		ErrorState=NOK;
	}
	return ErrorState;
}
