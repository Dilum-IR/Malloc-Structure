#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "mymalloc.h"

char memory[25000]; // declare global memory


// memory type cast to the head pointer type ->> void is use for any types
struct meta_block *head = (void *)memory; // point the head for first element in the memory array


void memorySplit(struct meta_block *Create_slot, size_t noOfBytes)
{

    // space split to that have current meta block and number of bytes that include
    struct meta_block *avali_space = (void *)Create_slot + noOfBytes + sizeof(struct meta_block);

    // remain space add to space sizer
    avali_space->size = Create_slot->size - noOfBytes - sizeof(struct meta_block); // avaliabel memory space size
    avali_space->free = 1; // avaliable space again free

    // avaliabel space next pointer to add creter slot had next pointer value
    avali_space->next = Create_slot->next;

    // initialize the newly create slot size
    Create_slot->size = noOfBytes;
    // initialize the newly create slot is not free
    Create_slot->free = 0;
    // initialize the newly create slot next pointer to avaliabel space pointer value
    Create_slot->next = avali_space;
}

int i = 0; // avaliabel no. of slot

void *MyMalloc(size_t noOfBytes)
{
    i = 1;

    struct meta_block *current;
    // return allocate memory block first elemnt memroy address store pointer variable
    void *output;

    if (!head->size) // head pointer create time size is null / 0
    {
        // 25000 byte - first create metablock size
        head->size = 25000 - sizeof(struct meta_block);
        head->free = 1;
        head->next = NULL;
        printf("\nInitialized the memory\n");
    }

    current = head;

    // condition: currnet block size greter than memory size or current block is free and current block to next metablock is not null
    while ((current->size < noOfBytes || current->free == 0) && current->next != NULL)
    {
        ++i; // avaliabel slots increment

        // optional condition 
        if (current->free = 0)
            printf("%d slot is already allocated \n", i);

        else
            printf("%d slot is already Free \n", i);

        current = current->next; // current pointer go to next block
    }

    /* condion :newly allocate memory block to want meta_block so, current size must greter than them */
    if (current->size > noOfBytes + sizeof(struct meta_block))
    {
        memorySplit(current, noOfBytes);
        output = (void *)++current;
        printf("\nMemory block is allocated...\n");

        return output;
    }
    /*  is this condition true,
    then that time memory allocated free slote to assign that slot */
    else if (current->size == noOfBytes)
    {
        current->free = 0;
        output = (void *)++current;
        printf("\nAllocated memory block to store that time...\n");
        return output;
    }

    else
    {
        output = NULL;
        printf("\nMemory block is not allocated.Beacuse memory's is not sufficient space for this allocation\n");
        return output;
    }
}

void freeMerge()
{
    int i = 0, k = 0;
    struct meta_block *merge;

    // initialize merge pointer to head meta block address
    merge = head;
    while (merge->next != NULL)
    {
        ++i;
        k = i;
        // check the cueent slot is free && next slot is free
        if (merge->free && merge->next->free)
        {
            ++k;
            // merge size  = current slot size + next slot size  + next meta block size
            // next meta block size = current meta block size
            merge->size = merge->size + merge->next->size + sizeof(merge->next);

            // currrent pointer go to next free slot pointer address
            merge->next = merge->next->next;
            printf("\n%d,%d Slots are merge Now\n", i, k);
        }
        // current pointer go to next slot pointer address
        merge = merge->next;
    }
}

void MyFree(void *freePtr)
{
    void *first = &memory[0];
    void *last = &memory[sizeof(memory)-1];
    
    // check freePtr inlcude in the created memory 0 and last index
    if (first <= freePtr && freePtr <= last)
    {
        struct meta_block *freeSlot;

        freeSlot = freePtr;
        --freeSlot; // Go to the free_slot meta block address
        freeSlot->free = 1;
        printf("memory slot now free. it's size %d\n", freeSlot->size);
        freeMerge();
    }
    else
        printf("This pointer is not avaliabel in MyMalloc.\nplease enter the valid pointer\n");
}
