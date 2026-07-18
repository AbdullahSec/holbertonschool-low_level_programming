#include "main.h"

/**
 * _strcpy - Copies string.
 * @dest: dest.
 * @src: src.
 * Return: dest.
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
