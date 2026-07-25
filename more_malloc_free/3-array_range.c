#include <stdlib.h>

/**
 * array_range - Creates an array of integers from min to max.
 * @min: Starting value (included).
 * @max: Ending value (included).
 *
 * Return: Pointer to newly created array, or NULL if min > max or malloc fails.
 */
int *array_range(int min, int max)
{
	int *array;
	int size, i;

	if (min > max)
		return (NULL);

	size = max - min + 1;
	array = malloc(sizeof(int) * size);
	if (array == NULL)
		return (NULL);

	for (i = 0; i < size; i++)
		array[i] = min + i;

	return (array);
}
