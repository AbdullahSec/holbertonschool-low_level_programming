#include "main.h"

/**
 * leet - Encodes a string into 1337.
 * @s: The string.
 *
 * Return: Pointer to string.
 */
char *leet(char *s)
{
	int i, j;
	char c[] = "aAeEoOtTlL";
	char n[] = "4433007711";

	for (i = 0; s[i] != '\0'; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (s[i] == c[j])
				s[i] = n[j];
		}
	}
	return (s);
}
