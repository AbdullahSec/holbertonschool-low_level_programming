#include "main.h"

/**
 * _strlen - Returns length of string.
 * @s: The string.
 *
 * Return: length.
 */
int _strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}
