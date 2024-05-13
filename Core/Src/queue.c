/*
 * queue.c
 *
 *  Created on: May 3, 2024
 *      Author: ahmet
 */

#include <stddef.h>
#include <stdint.h>

#include "kernel.h"

#define KERNEL_QUEUE_RAM_ADDR	0x0000FF00

typedef struct{
	size_t size;
	void* queue;
	void* head;
	void* tail;
}k_queue_t;//kernel queue

KERNEL_RETURN k_initQueue(k_queue_t* q)
{
	if((!q) || (q->size <= 0))
		return KERNEL_RETURN_FAILED;
	//q->queue =
	return KERNEL_RETURN_SUCCESS;
}

void k_enQueue()
{

}


void k_deQueue()
{

}

