#include "main.h"

/**
 * _puts - Prints a string.
 * @str: The string to print.
 *
 * Return: void.
 */
void _puts(char *str)
{
	int i = 0;

	while (str[i])
		_putchar(str[i++]);
	_putchar('\n');
}
