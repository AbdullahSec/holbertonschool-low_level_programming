#include "main.h"

/**
 * _atoi - Converts a string to an integer.
 * @s: The string to convert.
 *
 * Return: The integer value.
 */
int _atoi(char *s)
{
	int i = 0;
	int sign = 1;
	int flag = 0;
	unsigned int res = 0;

	while (s[i])
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			res = (res * 10) + (s[i] - '0');
		}
		else if (flag == 1)
			break;
		i++;
	}
	if (sign < 0)
		return (-res);
	return (res);
}
