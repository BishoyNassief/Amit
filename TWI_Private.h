/*
 * TWI_Private.h
 *
 *  Created on: Oct 16, 2021
 *      Author: andre
 */

#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_

#define TWCR	*((volatile u8*)0x56)
#define TWDR	*((volatile u8*)0x23)
#define TWAR	*((volatile u8*)0x22)
#define TWSR	*((volatile u8*)0x21)
#define TWBR	*((volatile u8*)0x20)


#define TWEN	2
#define TWINT	7
#define TWSTA	5
#define TWSTO	4
#define TWEA	6

#define PRESCALER_1			0
#define PRESCALER_4			1
#define PRESCALER_16		2
#define PRESCALER_64		3

#endif /* TWI_PRIVATE_H_ */
