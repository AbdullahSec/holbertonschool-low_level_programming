#include "main.h"

/**
 * cap_string - Capitalizes all words of a string.
 * @s: The string.
 *
 * Return: Pointer to string.
 */
char *cap_string(char *s)
{
	int i = 0, j;
	char sep[] = " \t\n,;.!?\"(){}";

	if (s[0] >= 'a' && s[0] <= 'z')
		s[0] -= 32;
	while (s[i])
	{
		for (j = 0; sep[j]; j++)
		{
			if (s[i] == sep[j] && s[i + 1] >= 'a' && s[i + 1] <= 'z')
				s[i + 1] -= 32;
		}
		i++;
	}
	return (s);
}
