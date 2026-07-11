#include <stdio.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int i;
	long int a, b, next;

	a = 1;
	b = 2;
	printf("%ld, %ld", a, b);
	i = 2;
	while (i < 50)
	{
		next = a + b;
		printf(", %ld", next);
		a = b;
		b = next;
		i++;
	}
	printf("\n");
	return (0);
}
