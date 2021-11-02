/*
 * TWI_Program.c
 *
 *  Created on: Oct 16, 2021
 *      Author: andre
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TWI_Private.h"
#include "TWI_Config.h"
#include "DIO_Interface.h"
#include <util/delay.h>


void TWI_voidInit(void)
{
	TWBR = 0x0C;
	TWSR = 0x00;

	TWAR = 0b00000010;
	TWCR = (1<<TWEN);
}



void TWI_voidStartCondition(void)
{
	/*
	 * Clear the TWINT flag before sending the start bit
	 * Send the start bit
	 * Enable the TWI
	 */
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	/*Wait for the TWINT flag to set*/
	while(!GET_BIT(TWCR,TWINT));
}

void TWI_voidStopCondition(void)
{

	/*	Clear the TWINT Flag before sending the stop bit
	 *  Send the stop bit
	 *  Enable the TWI
	 */
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}

void TWI_voidWrite(u8 Copy_u8Data)
{
	/*Put data on TWI data register*/
	TWDR = Copy_u8Data;
	/* Clear the TWINT Flag before sending the data
	 * Enable the TWI
	 */
	TWCR = (1<<TWINT) | (1<<TWEN);
	/*Wait for the TWINT flag to set,
	 *which indicates that the data was sent successfully*/
	while(!GET_BIT(TWCR,TWINT));
}

u8 TWI_u8ReadWithAck(void)
{
	/* Clear the TWINT flag
	 * Enable the Acknowledge bit
	 * Enable the TWI
	 */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	/*wait for the TWINT flag set to indicate that recieving was successful*/
	while(!GET_BIT(TWCR,TWINT));
	/*Read data*/
	return TWDR;
}

u8 TWI_u8ReadWithNAck(void)
{
	/* Clear the TWINT flag
	 * Enable the TWI
	 */
	TWCR = (1<<TWINT) | (1<<TWEN);
	/*wait for the TWINT flag set to indicate that recieving was successful*/
	while(!GET_BIT(TWCR,TWINT));
	/*Read data*/
	return TWDR;
}

u8 TWI_u8getStatus(void)
{
	u8 Status;
	/*masking the eliminate first 3 bits and get last 5 bits*/
	Status = TWSR & 0xF8;
	return Status;
}

