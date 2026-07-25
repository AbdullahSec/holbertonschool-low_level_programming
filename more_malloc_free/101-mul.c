#include <stdlib.h>

#if __has_include("main.h")
#include "main.h"
#endif

int _putchar(char c);

/**
 * print_error - Prints "Error" followed by a newline and exits with 98.
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
 * _strlen - Computes string length and validates if string contains only digits.
 * @s: Input string.
 *
 * Return: Length of string.
 */
static int _strlen(char *s)
{
	int len = 0;

	if (!s || !*s)
		print_error(); /* Fails on NULL or empty strings */

	while (s[len])
	{
		if (s[len] < '0' || s[len] > '9')
			print_error();
		len++;
	}
	return (len);
}

/**
 * perform_mul - Handles the core multiplication math.
 * @s1: First string.
 * @s2: Second string.
 * @result: Array to store the result.
 * @len1: Length of s1.
 * @len2: Length of s2.
 */
static void perform_mul(char *s1, char *s2, int *result, int len1, int len2)
{
	int i, j, carry, digit1, digit2;

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
	int len1, len2, len, i, *result, start = 0;

	if (argc != 3)
		print_error();

	s1 = argv[1];
	s2 = argv[2];
	len1 = _strlen(s1);
	len2 = _strlen(s2);
	len = len1 + len2;

	result = malloc(sizeof(int) * len);
	if (result == NULL)
		print_error();

	for (i = 0; i < len; i++)
		result[i] = 0;

	perform_mul(s1, s2, result, len1, len2);

	while (start < len - 1 && result[start] == 0)
		start++;

	for (i = start; i < len; i++)
		_putchar(result[i] + '0');
	_putchar('\n');

	free(result);
	return (0);
}
