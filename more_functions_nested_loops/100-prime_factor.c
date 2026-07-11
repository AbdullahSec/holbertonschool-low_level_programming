#include <stdio.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	long int n = 612852475143;
	long int f = 2;

	while (f * f <= n)
	{
		if (n % f == 0)
			n /= f;
		else
			f++;
	}
	printf("%ld\n", n);
	return (0);
}
