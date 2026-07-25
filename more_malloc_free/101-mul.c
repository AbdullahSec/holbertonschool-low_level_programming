#include "main.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * is_digit - checks if a string contains a non-digit
 * @s: string to be evaluated
 *
 * Return: 0 if a non-digit is found, 1 otherwise
 */
int is_digit(char *s)
{
	int i = 0;

	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * _strlen - returns the length of a string
 * @s: string to evaluate
 *
 * Return: the length of the string
 */
int _strlen(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

/**
 * errors - handles errors for main
 */
void errors(void)
{
	printf("Error\n");
	exit(98);
}

/**
 * multiply - multiplies two number strings into a digit array
 * @s1: first number string
 * @s2: second number string
 * @result: zero-filled array that receives the product digits
 */
void multiply(char *s1, char *s2, int *result)
{
	int i, j, carry, d1, d2;

	for (i = _strlen(s1) - 1; i >= 0; i--)
	{
		d1 = s1[i] - '0';
		carry = 0;
		for (j = _strlen(s2) - 1; j >= 0; j--)
		{
			d2 = s2[j] - '0';
			carry += result[i + j + 1] + (d1 * d2);
			result[i + j + 1] = carry % 10;
			carry /= 10;
		}
		if (carry > 0)
			result[i + j + 1] += carry;
	}
}

/**
 * main - multiplies two positive numbers
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: always 0 (Success)
 */
int main(int argc, char *argv[])
{
	int len, i, *result, a = 0;

	if (argc != 3 || !is_digit(argv[1]) || !is_digit(argv[2]))
		errors();
	len = _strlen(argv[1]) + _strlen(argv[2]);
	result = calloc(len, sizeof(int));
	if (!result)
		return (1);
	multiply(argv[1], argv[2], result);
	for (i = 0; i < len - 1; i++)
	{
		if (result[i])
			a = 1;
		if (a)
			_putchar(result[i] + '0');
	}
	_putchar(result[len - 1] + '0');
	_putchar('\n');
	free(result);
	return (0);
}
