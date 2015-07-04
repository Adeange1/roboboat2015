#include <stdio.h>
int counter=0;
int foo()
{
    printf("%d\n",counter++);
    return counter;
}