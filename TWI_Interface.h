/*
 * TWI_Interface.h
 *
 *  Created on: Oct 16, 2021
 *      Author: andre
 */

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_


/* I2C Status Bits in the TWSR Register */
#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave

void TWI_voidInit(void);
void TWI_voidStartCondition(void);
void TWI_voidStopCondition(void);
void TWI_voidWrite(u8 Copy_u8Data);
u8 TWI_u8ReadWithAck(void);
u8 TWI_u8ReadWithNAck(void);
u8 TWI_u8getStatus(void);


#endif /* TWI_INTERFACE_H_ */
