#include <stdio.h>
#include "variadic_functions.h"

/**
 * print_char - prints a char argument
 * @args: the variadic arguments list
 */
void print_char(va_list args)
{
	printf("%c", va_arg(args, int));
}

/**
 * print_int - prints an int argument
 * @args: the variadic arguments list
 */
void print_int(va_list args)
{
	printf("%d", va_arg(args, int));
}

/**
 * print_float - prints a float argument
 * @args: the variadic arguments list
 */
void print_float(va_list args)
{
	printf("%f", va_arg(args, double));
}

/**
 * print_string - prints a string argument, "(nil)" if NULL
 * @args: the variadic arguments list
 */
void print_string(va_list args)
{
	char *str;

	str = va_arg(args, char *);
	if (str == NULL)
		str = "(nil)";
	printf("%s", str);
}

/**
 * print_all - prints anything, based on a format string
 * @format: list of types of arguments (c, i, f, s); others ignored
 */
void print_all(const char * const format, ...)
{
	int i, j;
	char *sep;
	va_list args;
	printer_t printers[] = {
		{"c", print_char},
		{"i", print_int},
		{"f", print_float},
		{"s", print_string},
		{NULL, NULL}
	};

	va_start(args, format);
	i = 0;
	sep = "";
	while (format != NULL && format[i] != '\0')
	{
		j = 0;
		while (printers[j].symbol != NULL)
		{
			if (format[i] == printers[j].symbol[0])
			{
				printf("%s", sep);
				printers[j].print(args);
				sep = ", ";
			}
			j++;
		}
		i++;
	}
	va_end(args);
	printf("\n");
}
