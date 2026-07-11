#include "main.h"

/**
 * print_num - prints a number padded to 3 spaces
 * @p: the number to print
 */
void print_num(int p)
{
	if (p < 10)
	{
		_putchar(' ');
		_putchar(' ');
		_putchar(p + '0');
	}
	else if (p < 100)
	{
		_putchar(' ');
		_putchar((p / 10) + '0');
		_putchar((p % 10) + '0');
	}
	else
	{
		_putchar((p / 100) + '0');
		_putchar(((p / 10) % 10) + '0');
		_putchar((p % 10) + '0');
	}
}

/**
 * print_times_table - prints the n times table
 * @n: the table number
 */
void print_times_table(int n)
{
	int i, j;

	if (n < 0 || n > 15)
		return;
	for (i = 0; i <= n; i++)
	{
		_putchar('0');
		for (j = 1; j <= n; j++)
		{
			_putchar(',');
			_putchar(' ');
			print_num(i * j);
		}
		_putchar('\n');
	}
}
