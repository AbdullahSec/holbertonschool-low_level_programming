#include "main.h"

/**
* swap_int - is used to swap betwwen two pointers
*
* Return : void
*
* @a: has a value of 98
*
* @b: has a value of 42
**/


void swap_int(int *a, int *b)
{

int tmp;
tmp = 0;

tmp = *a;
*a = *b;
*b = tmp;

}
