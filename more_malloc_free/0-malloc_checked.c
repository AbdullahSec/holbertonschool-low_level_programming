#include "main.h"
#include <stdlib.h>

/**
 * malloc_checked - Allocates memory using malloc.
 * @b: Amount of bytes to allocate.
 *
 * Return: Pointer to allocated memory, or terminates process with 98.
 */
void *malloc_checked(unsigned int b)
{
	void *ptr;

	ptr = malloc(b);
	if (ptr == NULL)
		exit(98);

	return (ptr);
}
