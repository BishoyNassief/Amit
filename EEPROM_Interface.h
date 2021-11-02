/*
 * EEPROM_Interface.h
 *
 *  Created on: Oct 17, 2021
 *      Author: andre
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

void EEPROM_Init(void);
u8 EEPROM_Write_Byte(u16 address,u8 Copy_u8Data);
u8 EEPROM_Read_Byte(u16 address,u8 *Copy_u8Data);



#endif /* EEPROM_INTERFACE_H_ */
