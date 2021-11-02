/*
 * EEPROM_Program.c
 *
 *  Created on: Oct 17, 2021
 *      Author: andre
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "EEPROM_Private.h"
#include "EEPROM_Config.h"
#include "TWI_Config.h"
#include "TWI_Interface.h"
#include <util/delay.h>

void EEPROM_Init(void)
{
	TWI_voidInit();
}

u8 EEPROM_Write_Byte(u16 address,u8 Copy_u8Data)
{
	TWI_voidStartCondition();
	if(TWI_u8getStatus() != TW_START)
		return NOK;

	/*Write the slave address with write*/
	TWI_voidWrite((u8)(0xA0|((address & 0x0700)>>7)));
	if (TWI_u8getStatus() != TW_MT_SLA_W_ACK)
		return NOK;

	/*Send location address*/
	TWI_voidWrite((u8)(address));
	if(TWI_u8getStatus() != TW_MT_DATA_ACK)
		return NOK;

	/*Write byte to EEPROM*/
	TWI_voidWrite(Copy_u8Data);
	if(TWI_u8getStatus() != TW_MT_DATA_ACK)
		return NOK;

	TWI_voidStopCondition();
	return OK;

}

u8 EEPROM_Read_Byte(u16 address,u8 *Copy_u8Data)
{
	TWI_voidStartCondition();
	if(TWI_u8getStatus() != TW_START)
		return NOK;

	/*Write the slave address with write*/
	TWI_voidWrite((u8)(0xA0|((address & 0x0700)>>7)));
	if (TWI_u8getStatus() != TW_MT_SLA_W_ACK)
		return NOK;

	/*Send location address*/
	TWI_voidWrite((u8)(address));
	if(TWI_u8getStatus() != TW_MT_DATA_ACK)
		return NOK;

	/*Send a repeated start*/
	TWI_voidStartCondition();
	if(TWI_u8getStatus() != TW_REP_START)
		return NOK;

	/*Write the device address with read*/
	TWI_voidWrite((u8)( 0xA0 | ((address&0x0700)>>7) | 1 ));
	if(TWI_u8getStatus() != TW_MT_SLA_R_ACK)
		return NOK;

	*Copy_u8Data=TWI_u8ReadWithNAck();
	if(TWI_u8getStatus() != TW_MR_DATA_NACK)
		return NOK;

	TWI_voidStopCondition();
	return OK;
}
