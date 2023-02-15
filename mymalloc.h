#include <stdio.h>
#include <stddef.h>
#include <string.h>


struct meta_block
{
    size_t size;
    int free; /* memory block if free=1 then block is free
                  else free = 0 then block is not free */
    struct meta_block *next;
};


void freeMerge(); // memory space have free space and meta blocks then, merge them

void MyFree(void *); // if you want to free the used memory block then call the Myfree

void memorySplit(struct meta_block *Create_slot, size_t); // create the memory, you want size

void *MyMalloc(size_t size); // create memory spaces size and return the first block memory address in memory acclocate space 

