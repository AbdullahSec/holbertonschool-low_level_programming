#include "main.h"

/**
 * _strspn - Gets the length of a prefix substring.
 * @s: The string.
 * @accept: The accepted bytes.
 *
 * Return: Number of bytes.
 */
unsigned int _strspn(char *s, char *accept)
{
	unsigned int i, j, match;

	for (i = 0; s[i]; i++)
	{
		match = 0;
		for (j = 0; accept[j]; j++)
		{
			if (s[i] == accept[j])
			{
				match = 1;
				break;
			}
		}
		if (!match)
			break;
	}
	return (i);
}
