#include <stdio.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int i;
	unsigned long int a, b, next;
	unsigned long int a1, a2, b1, b2, n1, n2;

	a = 1;
	b = 2;
	printf("%lu, %lu", a, b);
	i = 2;
	while (i < 91)
	{
		next = a + b;
		printf(", %lu", next);
		a = b;
		b = next;
		i++;
	}
	a1 = a / 1000000000;
	a2 = a % 1000000000;
	b1 = b / 1000000000;
	b2 = b % 1000000000;
	while (i < 98)
	{
		n1 = a1 + b1;
		n2 = a2 + b2;
		if (n2 >= 1000000000)
		{
			n1 += 1;
			n2 -= 1000000000;
		}
		printf(", %lu%09lu", n1, n2);
		a1 = b1;
		a2 = b2;
		b1 = n1;
		b2 = n2;
		i++;
	}
	printf("\n");
	return (0);
}
