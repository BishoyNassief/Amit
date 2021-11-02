/*
 * PROJECT_Interface.h
 *
 *  Created on: Oct 27, 2021
 *      Author: Bishoy
 */

#ifndef PROJECT_INTERFACE_H_
#define PROJECT_INTERFACE_H_

#define TEMPSET			0
#define TEMPACTUAL		1


/*==================================================================*/

void HEATER_voidPower_Button	 (void);

void Heater_voidHeatingElementOn (void);
void Heater_voidHeatingElementOff(void);

void Heater_voidCoolingElementOn (void);
void Heater_voidCoolingElementOff(void);

void Heater_voidSensorON  (void);
void Heater_voidSensorOFF (void);


void Heater_voidLedON 	 (void);
void Heater_voidLedOFF 	 (void);

void Heater_voidLedToggle(void);

/*==================================================================*/

void HEATER_voidButtonDown_EXTI0 (void);
void HEATER_voidButtonUP_EXTI1   (void);

/*==================================================================*/

void HEATER_voidADC_Conversion(void);
void HEATER_voidADCSensorTempratureReading (void);
void HEATER_u8CompareTemperature(u8 Copy_u8SensorTemperature , u8 Copy_u8EnteredTemperature);

/*==================================================================*/

void OperationMode(u8 Copy_u8Mode);
u8 GlobalTempRead(void);
void SetGlobalTemp(u8 Copy_u8Val);
u8 ActTempRead(void);




#endif /* PROJECT_INTERFACE_H_ */
