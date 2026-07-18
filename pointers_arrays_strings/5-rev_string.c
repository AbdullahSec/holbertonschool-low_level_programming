#include "main.h"

/**
 * rev_string - Reverse string.
 * @s: string.
 * Return: void.
 */
void rev_string(char *s)
{
	int len = 0, i;
	char t;
	while (s[len])
		len++;
	for (i = 0; i < len / 2; i++)
	{
		t = s[i];
		s[i] = s[len - 1 - i];
		s[len - 1 - i] = t;
	}
}
