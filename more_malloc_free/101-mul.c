#include <stdlib.h>

#if __has_include("main.h")
#include "main.h"
#endif

/**
 * print_error - Prints "Error" followed by newline and exits with 98.
 */
static void print_error(void)
{
	char *err = "Error\n";
	int i;

	for (i = 0; err[i] != '\0'; i++)
		_putchar(err[i]);
	exit(98);
}

/**
 * is_digit - Checks if a string contains only digits.
 * @s: String to check.
 *
 * Return: 1 if all digits, 0 otherwise.
 */
static int is_digit(char *s)
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
 * _strlen - Returns the length of a string.
 * @s: String to evaluate.
 *
 * Return: Length of string.
 */
static int _strlen(char *s)
{
	int len = 0;

	while (s[len])
		len++;
	return (len);
}

/**
 * main - Multiplies two positive numbers passed as command-line arguments.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: Always 0 (Success).
 */
int main(int argc, char *argv[])
{
	char *s1, *s2;
	int len1, len2, len, i, j, carry, digit1, digit2, *result, start = 0;

	if (argc != 3)
		print_error();

	s1 = argv[1];
	s2 = argv[2];

	if (!is_digit(s1) || !is_digit(s2))
		print_error();

	len1 = _strlen(s1);
	len2 = _strlen(s2);
	len = len1 + len2;

	result = malloc(sizeof(int) * len);
	if (result == NULL)
		print_error();

	for (i = 0; i < len; i++)
		result[i] = 0;

	for (i = len1 - 1; i >= 0; i--)
	{
		digit1 = s1[i] - '0';
		carry = 0;
		for (j = len2 - 1; j >= 0; j--)
		{
			digit2 = s2[j] - '0';
			carry += result[i + j + 1] + (digit1 * digit2);
			result[i + j + 1] = carry % 10;
			carry /= 10;
		}
		if (carry > 0)
			result[i + j + 1] += carry;
	}

	while (start < len - 1 && result[start] == 0)
		start++;

	for (i = start; i < len; i++)
		_putchar(result[i] + '0');
	_putchar('\n');

	free(result);
	return (0);
}
