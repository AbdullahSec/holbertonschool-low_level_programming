#include <stdio.h>
#include <stdlib.h>

/**
 * main - prints the opcodes of its own main function
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 or 2 on error
 */
int main(int argc, char *argv[])
{
	int nbytes, i;
	char *opcode;

	if (argc != 2)
	{
		printf("Error\n");
		exit(1);
	}

	nbytes = atoi(argv[1]);
	if (nbytes < 0)
	{
		printf("Error\n");
		exit(2);
	}

	opcode = (char *)main;
	i = 0;
	while (i < nbytes)
	{
		printf("%02hhx", opcode[i]);
		if (i < nbytes - 1)
			printf(" ");
		i++;
	}
	printf("\n");
	return (0);
}
