#include <stdlib.h>
#include "main.h"

/**
 * is_digit - checks if a string contains only digits
 * @s: string to check
 *
 * Return: 1 if only digits, 0 otherwise
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
 * @s: string to measure
 *
 * Return: length of the string
 */
int _strlen(char *s)
{
	int len = 0;

	while (s[len])
		len++;
	return (len);
}

/**
 * errors - prints Error and exits with status 98
 */
void errors(void)
{
	char *msg = "Error\n";
	int i = 0;

	while (msg[i])
	{
		_putchar(msg[i]);
		i++;
	}
	exit(98);
}

/**
 * multiply - fills result array with product of s1 and s2
 * @s1: first number string
 * @s2: second number string
 * @result: output array
 * @len: length of result array
 */
void multiply(char *s1, char *s2, int *result, int len)
{
	int i, j, carry, d1, d2;

	for (i = 0; i < len; i++)
		result[i] = 0;
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
 * print_result - prints the result array without leading zeros
 * @result: array of digits
 * @len: length of array
 */
void print_result(int *result, int len)
{
	int i, started = 0;

	for (i = 0; i < len; i++)
	{
		if (result[i])
			started = 1;
		if (started)
			_putchar(result[i] + '0');
	}
	if (!started)
		_putchar('0');
	_putchar('\n');
}

/**
 * main - multiplies two positive numbers
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 98 on error
 */
int main(int argc, char *argv[])
{
	int len, *result;

	if (argc != 3 || !is_digit(argv[1]) || !is_digit(argv[2]))
		errors();
	len = _strlen(argv[1]) + _strlen(argv[2]) + 1;
	result = malloc(sizeof(int) * len);
	if (!result)
		return (1);
	multiply(argv[1], argv[2], result, len);
	print_result(result, len);
	free(result);
	return (0);

