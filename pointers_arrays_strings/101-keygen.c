#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * main - generates a random valid password for 101-crackme
 *
 * Return: Always 0
 */
int main(void)
{
	int sum = 0, c;

	srand(time(NULL));
	while (sum < 2650)
	{
		c = (rand() % 10) + 48;
		putchar(c);
		sum += c;
	}
	putchar(2772 - sum);
	return (0);
}
