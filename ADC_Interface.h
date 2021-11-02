/*
 * ADC_Interface.h
 *
 *  Created on: Sep 19, 2021
 *      Author: gerges
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

void ADC_voidInit(void);
u16 ADC_u16StartConversion(u8 Copy_u8Channel);
void ADC_voidInit_Interrupt(void);
void ADC_u16StartConversion_Interrupt(u8 Copy_u8Channel);
u16 ADC_u16DigitalRead(void);

void ADC_voidCallBackFunction(void (*Copy_PtrToFun)(void));

#endif /* ADC_INTERFACE_H_ */
