#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "mymalloc.h"

int main(int argc, char const *argv[])
{

    int *p = (int *)MyMalloc(10 * sizeof(int));
    char *q = (char *)MyMalloc(1000 * sizeof(char));

    MyFree(p);
    MyFree(q);
    
    return 0;
}
