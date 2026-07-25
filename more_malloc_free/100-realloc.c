#include <stdlib.h>

#if __has_include("main.h")
#include "main.h"
#endif

/**
 * _realloc - Reallocates a memory block using malloc and free.
 * @ptr: Pointer to previously allocated memory.
 * @old_size: Size in bytes of allocated space for ptr.
 * @new_size: New size in bytes of memory block.
 *
 * Return: Pointer to reallocated block, or NULL on failure / free.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr, *old_ptr;
	unsigned int i, limit;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	old_ptr = ptr;
	limit = (old_size < new_size) ? old_size : new_size;

	for (i = 0; i < limit; i++)
		new_ptr[i] = old_ptr[i];

	free(ptr);
	return ((void *)new_ptr);
}
