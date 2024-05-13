/*
 * memory.c
 *
 *  Created on: May 8, 2024
 *      Author: ahmet
 */


#include <stddef.h> // For size_t
#include <stdlib.h>

#include "kernel.h"
#include "memory.h"

#define MEMORY_NOTFREE 	0
#define MEMORY_FREE		1

#define POOL_SIZE 1024

struct block {
	unsigned int size;
    unsigned int top_addr;
    unsigned int base_addr;
    void* 	 	 payload;
    struct block *next;
};
typedef struct block block_t;

static char memory_pool[POOL_SIZE] __attribute__((section(".kernel")));
static block_t *kroot = NULL;

// Function to initialize the memory pool
void initialize_pool() {
	kroot = (block_t *)memory_pool;
	kroot->size = POOL_SIZE - sizeof(block_t);
	kroot->base_addr = KERNEL_RAM_START_ADDR;
	kroot->top_addr = KERNEL_RAM_START_ADDR + POOL_SIZE;
    //kroot->free = MEMORY_FREE;
    kroot->next = NULL;
}

// Function to allocate memory
void *kmalloc(size_t size)
{
    block_t *current_block = NULL;
    block_t *new_block = NULL;
    block_t *fitted_block = NULL;
    block_t *prev_block = NULL;
    void *result;

    if (!kroot) {
        // Initialize the memory pool if not already done
        initialize_pool();
        return kroot;
    }

    // Align size
    size = (size + sizeof(size_t) - 1) & ~(sizeof(size_t) - 1);

    unsigned int free_size = 0;

    current_block = kroot;
    prev_block = kroot;

	prev_block = current_block;
	current_block = current_block->next;

	if(!current_block)
	{

	}

    while(current_block != NULL)
    {
    	free_size = current_block->base_addr - prev_block->top_addr;
    	if(free_size >= size){
    		// adaquete area is found
    		new_block = (block_t*)prev_block->top_addr;
    	}
    	prev_block = current_block;
    	current_block = current_block->next;
    }


    if((fitted_block->size) >= (size + sizeof(block_t) + 4))
    {
    	new_block = (block_t *)((unsigned char *)fitted_block + size + sizeof(block_t));
    	new_block->top_addr = 0 + size;
    	new_block->base_addr = 0;
    }

    // Split the fitting block if it's larger than needed
    if ((fitted_block->size) >= (size + sizeof(block_t) + 4)) {
        block_t *new_block = (block_t *)((char *)fitted_block + size + sizeof(block_t));
        new_block->size = (fitted_block->size) - size - sizeof(block_t);
        new_block->next = fitted_block->next;

        fitted_block->size = size;
        fitted_block->next = new_block;
    }


    // Return a pointer to the allocated memory
    result = (void *)((char *)fitted_block + sizeof(block_t));
    return result;
}


