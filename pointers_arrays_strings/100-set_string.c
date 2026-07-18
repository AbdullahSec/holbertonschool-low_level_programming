#include "main.h"

/**
 * set_string - Sets the value of a pointer to a char.
 * @s: The pointer to change.
 * @to: The string to point to.
 *
 * Return: void.
 */
void set_string(char **s, char *to)
{
	*s = to;
}
