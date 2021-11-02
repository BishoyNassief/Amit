/*
 * SEVEN_SEGMENT_Interface.h
 *
 *  Created on: Oct 28, 2021
 *      Author: Bishoy
 */

#ifndef SEVEN_SEGMENT_INTERFACE_H_
#define SEVEN_SEGMENT_INTERFACE_H_


#define ENABLED		1
#define DISABLED	0

void Timer0_Interrupt_Function(void);


void SEVEN_SEGMENT_voidEnable (void);
void SEVEN_SEGEMENT_u8SendNumber (u8 Copy_u8Number);

void SEVEN_SEGMENT_voidON (void);
void SEVEN_SEGMENT_voidOFF (void);

void SEVEN_SEGMENT_voidBlink(u32 BLINKTIME_ms);
u8 SEVEN_SEGMENT_GetBlinkingStatus(void);





#endif /* SEVEN_SEGMENT_INTERFACE_H_ */
