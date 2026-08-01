#include <stdio.h>
#include <stdlib.h>

/**
 * main - prints the minimum number of coins to make change for an amount
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 if the wrong number of arguments is given
 */
int main(int argc, char *argv[])
{
	int cents, coins;
	int values[] = {25, 10, 5, 2, 1};
	int i;

	if (argc != 2)
	{
		printf("Error\n");
		return (1);
	}

	cents = atoi(argv[1]);
	if (cents < 0)
	{
		printf("0\n");
		return (0);
	}

	coins = 0;
	i = 0;
	while (cents > 0)
	{
		coins += cents / values[i];
		cents = cents % values[i];
		i++;
	}
	printf("%d\n", coins);
	return (0);
}
