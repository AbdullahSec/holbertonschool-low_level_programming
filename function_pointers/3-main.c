#include "3-calc.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * main - performs simple math operations based on command-line arguments
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: result of the operation, or exits with an error status
 */
int main(int argc, char *argv[])
{
	int a, b;
	int (*func)(int, int);

	if (argc != 4)
	{
		printf("Error\n");
		exit(98);
	}

	func = get_op_func(argv[2]);
	if (func == NULL)
	{
		printf("Error\n");
		exit(99);
	}

	a = atoi(argv[1]);
	b = atoi(argv[3]);

	if ((argv[2][0] == '/' || argv[2][0] == '%') && b == 0)
	{
		printf("Error\n");
		exit(100);
	}

	printf("%d\n", func(a, b));
	return (0);
}
