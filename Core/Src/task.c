/*
 * task.c
 *
 *  Created on: May 2, 2024
 *      Author: ahmet
 */

#include <stdlib.h>

#include "kernel.h"
#include "task.h"


#define STM32_F446RE_RAM_START_ADDR		0x00000000

//k_task_t wait_queue[MAX_TASK_COUNT] = {0};
//k_task_t ready_queue[MAX_TASK_COUNT] = {0};

task_t *idle_task = NULL;
task_t *utask_parent = NULL; // user task parent


static int assign_taskID()
{
	return 0;//TODO assign task id
}

void push_stackRegister(reg_t *r)
{
	/*reg_t *regs = r;
	// low registers
	__asm__ ("MOV R0, %0\n" : "=r" (regs->r0));
	__asm__ ("MOV R1, %0\n" : "=r" (regs->r1));
	__asm__ ("MOV R2, %0\n" : "=r" (regs->r2));
	__asm__ ("MOV R3, %0\n" : "=r" (regs->r3));
	__asm__ ("MOV R4, %0\n" : "=r" (regs->r4));
	__asm__ ("MOV R5, %0\n" : "=r" (regs->r5));
	__asm__ ("MOV R6, %0\n" : "=r" (regs->r6));
	__asm__ ("MOV R7, %0\n" : "=r" (regs->r7));
	// High registers
	__asm__ ("MOV R8, %0\n" : "=r" (regs->r8));
	__asm__ ("MOV R9, %0\n" : "=r" (regs->r9));
	__asm__ ("MOV R10, %0\n" : "=r" (regs->r10));
	__asm__ ("MOV R11, %0\n" : "=r" (regs->r11));
	__asm__ ("MOV R12, %0\n" : "=r" (regs->r12));
	__asm__ ("MOV R13, %0\n" : "=r" (regs->r13));
	__asm__ ("MOV R14, %0\n" : "=r" (regs->r14));
	__asm__ ("MOV R15, %0\n" : "=r" (regs->r15));

	__asm__("PUSH {r0-r14}");*/
}

KERNEL_RETURN kernal_enQueue(task_t *t)
{
	for(int i=0; i<MAX_TASK_COUNT; ++i)
	{
		if(t->s == 0)
			continue;

		break;
	}

	return KERNEL_RETURN_SUCCESS;
}

task_t* task_createKernel()
{
	if(!idle_task)
	{
		idle_task = (task_t*)malloc(sizeof(task_t));
		idle_task->s = Initialised;
		idle_task->t_id = 0;
		idle_task->next = NULL;
		return idle_task;
	}

	task_t *new_task = idle_task;

	while(new_task->next != NULL)
		new_task = new_task->next;

	if(!new_task->next)
	{
		new_task = (task_t*)malloc(sizeof(task_t));//TODO replace with kmalloc()
		new_task->s = Initialised;
		new_task->t_id = assign_taskID();
		new_task->next = NULL;
	}

	return new_task;
}

task_t* task_createUser()
{
	if(!utask_parent)
	{
		utask_parent = (task_t*)malloc(sizeof(task_t));
		utask_parent->s = Initialised;
		utask_parent->t_id = 0;
		utask_parent->next = NULL;
		return utask_parent;
	}

	task_t *new_task = utask_parent;

	while(new_task->next != NULL)
		new_task = new_task->next;

	if(!new_task->next)
	{
		new_task = (task_t*)malloc(sizeof(task_t));
		new_task->s = Initialised;
		new_task->t_id = assign_taskID();
		new_task->next = NULL;
	}

	return new_task;
}

KERNEL_RETURN task_terminateKernel(int t_id)
{
	task_t *k_task = idle_task;
	task_t *prev_task = idle_task;
	while(k_task->next != NULL)
	{
		k_task = k_task->next;
		if((k_task->t_id == t_id) && (k_task->t_id != 0))// 0 task id always belongs with idle and user task parent
		{
			prev_task->next = k_task->next;
			free(k_task);
			break;
		}
		prev_task = prev_task->next;
	}

	return KERNEL_RETURN_SUCCESS;
}

void task_pending(task_t* t)
{
	if(!t){

	}

}

void scheduler_switchContext(task_t *t)
{

}






