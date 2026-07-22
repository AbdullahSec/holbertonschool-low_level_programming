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

	/* Step 1: Check if input string is NULL */
	if (str == NULL)
		return (NULL);

	/* Step 2: Calculate the length of str */
	while (str[length] != '\0')
	{
		length++;
	}

	/* Step 3: Allocate memory for the new string (length + 1 for '\0') */
	s = malloc((length + 1 ) * sizeof(char));
	{

	
		
	

	/* Step 4: Check if malloc failed */
	if (s == NULL)
		return (NULL);
	}
	/* :Step 5: Copy characters from str to s */
	for (; i <= length; i++)
	{
		s[i] = str[i];
	}

	/* Step 6: Add the null terminator at the end */
	/* s[i] = '\0';{     */

		return (s);
}




