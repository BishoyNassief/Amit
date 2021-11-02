/*
 * TIMER1_Interface.h
 *
 *  Created on: Sep 27, 2021
 *      Author: Eman
 */

#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

void TIMER1_voidInit(void);
void TIMER1_voidSetICR1Value(u16 Copy_u16ICR1Value);
void TIMER1_voidSetOCR1AValue(u16 Copy_u16OCR1AValue);
void TIMER1_voidCallBackFunction(void (*Copy_PReturnFunction)(void));

#endif /* TIMER1_INTERFACE_H_ */
