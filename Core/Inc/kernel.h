/*
 * kernel.h
 *
 *  Created on: May 3, 2024
 *      Author: ahmet
 */

#ifndef INC_KERNEL_H_
#define INC_KERNEL_H_

typedef unsigned int KERNEL_RETURN;

#define KERNEL_RETURN_FAILED	0x00000000
#define	KERNEL_RETURN_SUCCESS	0x00000001

#define KERNEL_RAM_START_ADDR	0x20000000

#endif /* INC_KERNEL_H_ */
