/*
 * EXTI_Private.h
 *
 *  Created on: Sep 12, 2021
 *      Author: gerges
 */

#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

#define MCUCR    *((volatile u8*)(0x55))
#define MCUCSR   *((volatile u8*)(0x54))
#define GICR     *((volatile u8*)(0x5B))

#define EXTI_FALLING_EDGE 0
#define EXTI_RISING_EDGE         1
#define EXTI_ANY_LOGICAL_CHANGE  2
#define EXTI_LOW_LEVEL           3

#endif /* EXTI_PRIVATE_H_ */
