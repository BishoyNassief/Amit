/*
 * PROJECT_Program.c
 *
 *  Created on: Oct 27, 2021
 *      Author: Bishoy
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Config.h"
#include "DIO_Private.h"
#include "DIO_Interface.h"
#include "ADC_Private.h"
#include "ADC_Config.h"
#include "ADC_Interface.h"


#include "EXTI_Interface.h"
#include "SEVEN_SEGMENT_Interface.h"


#include "PROJECT_Interface.h"

#include <util/delay.h>

u8 DEVICE_ON_OFF_FLAG=1;
u8 FUNCTIONS_ON_OFF_FLAG=1;
u8  Global_Temperature = 60;
f32 Sensor_Temperature =0;
u8 ADC_Enable_Flag=1;

u8 i = 0 , j , k;
u16 AnalogReadArr[10] = {};
f32 AnalogReading =0 , DigitalReading =0;




/*==================================================================*/
void Heater_voidHeatingElementOn (void)
{
	DIO_u8SetPinValue(DIO_PIN4,DIO_PORTC, PIN_HIGH);
}
void Heater_voidHeatingElementOff(void)
{
	DIO_u8SetPinValue(DIO_PIN4,DIO_PORTC, PIN_LOW);
}

void Heater_voidCoolingElementOn (void)
{
	DIO_u8SetPinValue(DIO_PIN2,DIO_PORTC, PIN_HIGH);
}
void Heater_voidCoolingElementOff(void)
{
	DIO_u8SetPinValue(DIO_PIN2,DIO_PORTC, PIN_LOW);
}

void Heater_voidLedON (void)
{
	DIO_u8SetPinValue(DIO_PIN7 ,DIO_PORTB , PIN_HIGH);
}
void Heater_voidLedOFF (void)
{
	DIO_u8SetPinValue(DIO_PIN7 ,DIO_PORTB , PIN_LOW);

}

void Heater_voidSensorON (void)
{
	DIO_u8SetPinValue(DIO_PIN0 ,DIO_PORTA , PIN_HIGH);
}
void Heater_voidSensorOFF (void)
{
	DIO_u8SetPinValue(DIO_PIN0 ,DIO_PORTA , PIN_LOW);

}

void Heater_voidLedToggle(void)
{
	DIO_u8SetPinValue(DIO_PIN7 ,DIO_PORTB , PIN_LOW);
	_delay_ms(1000);
	DIO_u8SetPinValue(DIO_PIN7 ,DIO_PORTB , PIN_HIGH);
	_delay_ms(1000);
}
/*==================================================================*/

void HEATER_voidPower_Button(void)
{
	if (DEVICE_ON_OFF_FLAG == 1)
	{
		SEVEN_SEGMENT_voidON();
		SEVEN_SEGEMENT_u8SendNumber(00);

		DEVICE_ON_OFF_FLAG = 0;
		FUNCTIONS_ON_OFF_FLAG=1;
	}
	else if (DEVICE_ON_OFF_FLAG == 0)
	{
		Heater_voidHeatingElementOff();
		Heater_voidCoolingElementOff();
		SEVEN_SEGMENT_voidOFF();
		Heater_voidSensorOFF();
		Heater_voidLedOFF();

		DEVICE_ON_OFF_FLAG = 1;
		FUNCTIONS_ON_OFF_FLAG=0;
	}
	else {
		/*Nothing*/
	}
}

/*==================================================================*/

void HEATER_voidButtonUP_EXTI1 (void)
{
	if(FUNCTIONS_ON_OFF_FLAG==1)
	{
		if(Global_Temperature<75)
		{
			Global_Temperature+=5;
		}
		SEVEN_SEGMENT_voidBlink(5000);
	}
	else
	{
		/*nothing*/
	}
}

void HEATER_voidButtonDown_EXTI0 (void)
{
	if(FUNCTIONS_ON_OFF_FLAG==1)
	{
		if(Global_Temperature>35)
		{
			Global_Temperature-=5;
		}
		SEVEN_SEGMENT_voidBlink(5000);

	}
	else
	{
		/*nothing*/
	}
}

/*==================================================================*/

void HEATER_voidADC_Conversion(void)
{
	//Check flag to see if we are in temp actual mode
	if(ADC_Enable_Flag==1)
	{
	ADC_u16StartConversion_Interrupt(0);
	}
	else;
}

/*==================================================================*/

void HEATER_u8CompareTemperature(u8 Copy_u8SensorTemperature , u8 Copy_u8EnteredTemperature)
{
	if (FUNCTIONS_ON_OFF_FLAG == 1)
	{
		if (Copy_u8SensorTemperature > Copy_u8EnteredTemperature)
		{
			Heater_voidHeatingElementOff();
			Heater_voidCoolingElementOn ();
			Heater_voidLedON();
		}
		else if (Copy_u8SensorTemperature < Copy_u8EnteredTemperature)
		{
			Heater_voidHeatingElementOn();
			Heater_voidCoolingElementOff ();

		}
		else
		{
			Heater_voidHeatingElementOff();
			Heater_voidCoolingElementOff ();
			Heater_voidLedOFF();
		}
	}
}

/*==================================================================*/

void HEATER_voidADCSensorTempratureReading(void)
{
	if(i!=10)
	{
		AnalogReadArr[i]=ADC_u16DigitalRead();
		i++;
	}else
	{
		//NOTHING
	}

	if(AnalogReadArr[9] != 0)
	{
		/*Get average of 10 readings*/
		u16 LOC_u16AverageReading=0;
		for(j=0;j<10;j++)
		{
			LOC_u16AverageReading=LOC_u16AverageReading+AnalogReadArr[j];
		}
		LOC_u16AverageReading=LOC_u16AverageReading/10;
		AnalogReading=LOC_u16AverageReading;

		/*convert to digital reading*/
		DigitalReading = (AnalogReading)/2.0537F;
		/*Display reading on 7 segment*/

		SEVEN_SEGEMENT_u8SendNumber(DigitalReading);

		for(k=0;k<10;k++)
		{
			AnalogReadArr[k]=0;
		}
		i=0;
	}
	else
	{
		//NOTHING
	}

//	for (u8 Reading_count = 0 ; Reading_count <= 9; Reading_count ++)
//	{
//		LastTenReadingsArr[Reading_count]=ADC_u16DigitalRead();
//
//		if (Reading_count == 9)
//
//		{
//			for(count=0 ; count < 10 ; count ++)
//			{
//				Sum_of_ten_Temperatures += LastTenReadingsArr[count];
//			}
//			Sensor_Temperature=(Sum_of_ten_Temperatures/10);
////			Sensor_Temperature= (Sensor_Temperature/2)-1;
//		}
//		else;
//	}
}

/*==================================================================*/

void OperationMode(u8 Copy_u8Mode)
{
	if(Copy_u8Mode==TEMPSET)
	{
		//In setting temp mode we disable the ADC
		ADC_Enable_Flag=0;
		/*display the set temperature*/
		SEVEN_SEGEMENT_u8SendNumber(Global_Temperature);


	}
	else if(Copy_u8Mode==TEMPACTUAL)
	{
		//In actual temp mode we enable the ADC
		ADC_Enable_Flag=1;
	}
	else
	{

	}

}

u8 GlobalTempRead(void)
{
	return Global_Temperature;
}

void SetGlobalTemp(u8 Copy_u8Val)
{
	Global_Temperature=Copy_u8Val;
}

u8 ActTempRead(void)
{
	return DigitalReading;
}
 void Toggle_LedHeater (void)
 {
	 DIO_u8SetPinValue(DIO_PIN5 , DIO_PORTC , PIN_HIGH);
	 _delay_ms(1000);
	 DIO_u8SetPinValue(DIO_PIN5 , DIO_PORTC , PIN_LOW);
	 _delay_ms(1000);
 }
