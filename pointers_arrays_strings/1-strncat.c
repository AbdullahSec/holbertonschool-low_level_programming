#include "main.h"

/**
 * _strncat - Concatenates two strings.
 * @dest: Destination string.
 * @src: Source string.
 * @n: Maximum bytes.
 *
 * Return: Pointer to dest.
 */
char *_strncat(char *dest, char *src, int n)
{
	int i = 0, j = 0;

	while (dest[i])
		i++;
	while (j < n && src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
