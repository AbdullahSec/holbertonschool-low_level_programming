#include <stdio.h>
#include "variadic_functions.h"

/**
 * print_strings - prints strings separated by a given separator
 * @separator: the string printed between strings (not printed if NULL)
 * @n: the number of strings passed to the function
 */
void print_strings(const char *separator, const unsigned int n, ...)
{
	unsigned int i;
	char *str;
	va_list args;

	va_start(args, n);
	i = 0;
	while (i < n)
	{
		str = va_arg(args, char *);
		if (str == NULL)
			printf("(nil)");
		else
			printf("%s", str);
		if (separator != NULL && i < n - 1)
			printf("%s", separator);
		i++;
	}
	va_end(args);
	printf("\n");
}
