#include "main.h"

/**
 * rot13 - Encodes a string using rot13.
 * @s: The string.
 *
 * Return: Pointer to s.
 */
char *rot13(char *s)
{
	int i, j;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	for (i = 0; s[i] != '\0'; i++)
	{
		for (j = 0; in[j] != '\0'; j++)
		{
			if (s[i] == in[j])
			{
				s[i] = out[j];
				break;
			}
		}
	}
	return (s);
}
