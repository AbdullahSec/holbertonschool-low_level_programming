#include "main.h"

/**
 * _strncpy - Copies a string.
 * @dest: Destination string.
 * @src: Source string.
 * @n: Maximum bytes.
 *
 * Return: Pointer to dest.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i = 0;

	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
