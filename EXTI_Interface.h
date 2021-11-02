/*
 * EXTI_Interface.h
 *
 *  Created on: Sep 12, 2021
 *      Author: gerges
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

void EXTI_voidINT0_Init(void);
void EXTI_voidINT1_Init(void);
void EXTI_voidINT2_Init(void);
void EXTI_voidSet_SenseControl(u8 Copy_u8SenseControl);

void EXTI0_voidCallBackFunction(void (*Copy_PtrToFun)(void));
void EXTI1_voidCallBackFunction(void (*Copy_PtrToFun)(void));
void EXTI2_voidCallBackFunction(void (*Copy_PtrToFun)(void));


#endif /* EXTI_INTERFACE_H_ */
