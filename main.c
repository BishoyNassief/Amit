/*
 * PROJECT_main.c

 *
 *  Created on: Oct 27, 2021
 *      Author: Bishoy
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include "DIO_Interface.h"
#include "DIO_Private.h"

#include "EEPROM_Config.h"
#include "EEPROM_Interface.h"
#include "TWI_Config.h"
#include "TWI_Interface.h"

#include "SEVEN_SEGMENT_Interface.h"

#include "ADC_Config.h"
#include "ADC_Interface.h"
#include"EXTI_Interface.h"
#include"GIE_Interface.h"

#include "TIMER_Config.h"
#include "TIMER1_Config.h"
#include "Timer_Interface.h"
#include "TIMER1_Interface.h"

#include "PROJECT_Interface.h"
//#include <util/delay.h>


u8 Temp1;
u8 SensorReading,SetTemperature;
int main (void)
{
	/*Set three buttons as Pull Up*/
	DIO_u8SetPinValue(DIO_PIN2,DIO_PORTD,PIN_HIGH);
	DIO_u8SetPinValue(DIO_PIN3,DIO_PORTD,PIN_HIGH);
	DIO_u8SetPinValue(DIO_PIN2,DIO_PORTB,PIN_HIGH);

	/*Set EXT0 PIN as an interrupt for Down button*/
	DIO_u8SetPinDirection(DIO_PIN2,DIO_PORTD,PIN_INPUT);
	/*Set EXT1 PIN as an interrupt for up button*/
	DIO_u8SetPinDirection(DIO_PIN3,DIO_PORTD,PIN_INPUT);
	/*Set EXT2 PIN as an interrupt for Power button*/
	DIO_u8SetPinDirection(DIO_PIN2,DIO_PORTB,PIN_INPUT);

	/*Set some test leds */
	DIO_u8SetPinDirection(DIO_PIN5,DIO_PORTD,PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PIN7,DIO_PORTB,PIN_OUTPUT);

	/*Call back functions for Up and down buttons*/
	EXTI0_voidCallBackFunction(&HEATER_voidButtonDown_EXTI0);
	EXTI1_voidCallBackFunction(&HEATER_voidButtonUP_EXTI1);
	EXTI2_voidCallBackFunction(&HEATER_voidPower_Button);

	/*Call back function timer 0*/
	TIMER0_voidSet_CallBackfunction(&Timer0_Interrupt_Function);

	/*Call back function for ADC conversion for timer 1*/
	TIMER1_voidCallBackFunction(&HEATER_voidADC_Conversion);
	TIMER1_voidSetOCR1AValue(1560);
	ADC_voidCallBackFunction(&HEATER_voidADCSensorTempratureReading);

	/*Enable Global interrupts*/
	GIE_voidEnable();

	/*Enable external interrupts*/
	EXTI_voidINT0_Init();
	EXTI_voidINT1_Init();
	EXTI_voidINT2_Init();

	/*SEVEN SEGMENT initialization */
	SEVEN_SEGMENT_voidEnable();

	/*ADC initialization*/
	ADC_voidInit_Interrupt();

	/*TIMER1 initialization*/
	TIMER1_voidInit();

	/*EEPROM init*/
	EEPROM_Init();
	u16 AddressTemp = 0x0002;

	/*Set pin direction for heater and cooler*/
	DIO_u8SetPinDirection(DIO_PIN2 , DIO_PORTC , PIN_OUTPUT);
	DIO_u8SetPinDirection(DIO_PIN4 , DIO_PORTC , PIN_OUTPUT);


	Heater_voidHeatingElementOff();
	Heater_voidCoolingElementOff();
	SEVEN_SEGMENT_voidOFF();
	Heater_voidSensorOFF();
	Heater_voidLedOFF();

	/*read the EEPROM Value*/
	EEPROM_Read_Byte(AddressTemp,&Temp1);
	SetGlobalTemp(Temp1);

	/*By default the temp displayed is the actual one*/
	OperationMode(TEMPACTUAL);

	while(1)
	{
		if(SEVEN_SEGMENT_GetBlinkingStatus()==ENABLED)
		{
			/*If the blinking is on then we display the set temperature*/
			OperationMode(TEMPSET);
		}
		else
		{
			if(Temp1 != GlobalTempRead())
			{
				Temp1 = GlobalTempRead();
				EEPROM_Write_Byte(AddressTemp,Temp1);
			}
			OperationMode(TEMPACTUAL);
		}

		SensorReading = ActTempRead();
		SetTemperature = GlobalTempRead();
		HEATER_u8CompareTemperature(SensorReading,SetTemperature);
	}
	return 0;
}



