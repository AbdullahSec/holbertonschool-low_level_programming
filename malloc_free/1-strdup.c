#include "main.h"
#include <stdlib.h>

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 *           which contains a copy of the string given as a parameter.
 * @str: string to duplicate
 *
 * Return: pointer to duplicated string, or NULL if fail/str is NULL
 */
char *_strdup(char *str)
{
	char *s;
	unsigned int length = 0;
	unsigned int i = 0;

	if (str == NULL)
		return (NULL);

	while (str[length] != '\0')
	{
		length++;
	}

	s = malloc((length + 1) * sizeof(char));
	if (s == NULL)
	{
		return (NULL);
	}

	for (; i <= length; i++)
	{
		s[i] = str[i];
	}

	/* Step 6: Add the null terminator at the end */
	/* s[i] = '\0';{     */

		return (s);

}




