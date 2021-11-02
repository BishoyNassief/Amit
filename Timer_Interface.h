/*
 * Timer_Interface.h
 *
 *  Created on: 21 Sep 2021
 *      Author: Viro
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

void TIMER0_voidInit(void);
void TIMER0_voidSetPrLoad(u8 Copy_u8Preload);
void TIMER0_voidSetCTCValue(u8 Copy_u8CTC_Value);
void TIMER0_voidSet_CallBackfunction(void(*Copy_voidP_CallBackFun)(void));


#endif /* TIMER_INTERFACE_H_ */
