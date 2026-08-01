#include <stdio.h>
#include "variadic_functions.h"

/**
 * print_all - prints anything, based on a format string
 * @format: list of types of arguments (c, i, f, s); others ignored
 */
void print_all(const char * const format, ...)
{
	int i;
	char *str;
	char *sep;
	va_list args;

	va_start(args, format);
	i = 0;
	sep = "";
	while (format != NULL && format[i] != '\0')
	{
		if (format[i] == 'c')
			printf("%s%c", sep, va_arg(args, int));
		if (format[i] == 'i')
			printf("%s%d", sep, va_arg(args, int));
		if (format[i] == 'f')
			printf("%s%f", sep, va_arg(args, double));
		if (format[i] == 's')
		{
			str = va_arg(args, char *);
			if (str == NULL)
				str = "(nil)";
			printf("%s%s", sep, str);
		}
		if (format[i] == 'c' || format[i] == 'i' ||
			format[i] == 'f' || format[i] == 's')
			sep = ", ";
		i++;
	}
	va_end(args);
	printf("\n");
}
