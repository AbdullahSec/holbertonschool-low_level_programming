#include "function_pointers.h"

/**
 * int_index - searches for an integer using a comparison function
 * @array: the array to search
 * @size: the number of elements in the array
 * @cmp: pointer to the comparison function
 *
 * Return: index of the first matching element, or -1 if none / size <= 0
 */
int int_index(int *array, int size, int (*cmp)(int))
{
	int i;

	if (array == NULL || cmp == NULL)
		return (-1);
	if (size <= 0)
		return (-1);

	i = 0;
	while (i < size)
	{
		if (cmp(array[i]) != 0)
			return (i);
		i++;
	}
	return (-1);
}
