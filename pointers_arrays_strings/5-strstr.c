#include "main.h"
#include <stddef.h>

/**
 * _strstr - Locates a substring.
 * @haystack: The string.
 * @needle: The substring.
 *
 * Return: Pointer to substring or NULL.
 */
char *_strstr(char *haystack, char *needle)
{
	int i, j;

	if (*needle == 0)
		return (haystack);
	for (i = 0; haystack[i]; i++)
	{
		for (j = 0; needle[j]; j++)
		{
			if (haystack[i + j] != needle[j])
				break;
		}
		if (needle[j] == '\0')
			return (haystack + i);
	}
	return (NULL);
}
