#include "main.h"
#include <stdio.h>

/**
 * print_buffer - Prints a buffer.
 * @b: The buffer.
 * @size: The size.
 *
 * Return: void.
 */
void print_buffer(char *b, int size)
{
	int offset, i;

	if (size <= 0)
	{
		printf("\n");
		return;
	}
	for (offset = 0; offset < size; offset += 10)
	{
		printf("%08x:", offset);
		for (i = 0; i < 10; i++)
		{
			if (i % 2 == 0)
				printf(" ");
			if (offset + i < size)
				printf("%02x", *(b + offset + i));
			else
				printf("  ");
		}
		printf(" ");
		for (i = 0; i < 10; i++)
		{
			if (offset + i < size)
			{
				if (*(b + offset + i) >= 32 && *(b + offset + i) <= 126)
					printf("%c", *(b + offset + i));
				else
					printf(".");
			}
		}
		printf("\n");
	}
}
