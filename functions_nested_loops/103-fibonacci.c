#include <stdio.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	long int a, b, next, sum;

	a = 1;
	b = 2;
	sum = 2;
	while (b < 4000000)
	{
		next = a + b;
		if (next % 2 == 0)
			sum += next;
		a = b;
		b = next;
	}
	printf("%ld\n", sum);
	return (0);
}
