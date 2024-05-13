/*
 * task.h
 *
 *  Created on: May 3, 2024
 *      Author: ahmet
 */

#ifndef INC_TASK_H_
#define INC_TASK_H_

#include <stdint.h>
#include <stdlib.h>


#define TASK_MAX_SIZE		1024*8
#define TASK_MAX_SIZE		512*1
#define MAX_TASK_COUNT		16

typedef void (*create_task_t)(void* arg);

typedef enum{
	Initialised = 0x0001,
	Ready,
	Waiting,
	Blocked,
	Terminated
}state_t;

typedef struct{
	unsigned int r0;
	unsigned int r1;
	unsigned int r2;
	unsigned int r3;
	unsigned int r4;
	unsigned int r5;
	unsigned int r6;
	unsigned int r7;
	unsigned int r8;
	unsigned int r9;
	unsigned int r10;
	unsigned int r11;
	unsigned int r12;
	unsigned int r13;// sp (psp and msp)
	unsigned int r14;// lr
	unsigned int r15;// pc
}reg_t;

struct task{
	int 		t_id;
	reg_t		regs;
	size_t		stack_size;
	size_t  	heap_size;
	int8_t		priority;
	uint8_t		s;
	create_task_t task_p;
	struct task* next;
};// kernel task
typedef struct task task_t;

task_t* task_createKernel();

task_t* task_createUser();

#endif /* INC_TASK_H_ */
