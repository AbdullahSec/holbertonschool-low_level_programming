#include "main.h"

/**
 * infinite_add - Adds two numbers.
 * @n1: First number.
 * @n2: Second number.
 * @r: Buffer.
 * @size_r: Buffer size.
 *
 * Return: Pointer to r or 0 if error.
 */
char *infinite_add(char *n1, char *n2, char *r, int size_r)
{
	int l1 = 0, l2 = 0, sum = 0, i, j, k = 0, l;
	char tmp;

	while (n1[l1])
		l1++;
	while (n2[l2])
		l2++;
	if (l1 >= size_r || l2 >= size_r)
		return (0);
	i = l1 - 1;
	j = l2 - 1;
	while (i >= 0 || j >= 0 || sum == 1)
	{
		if (i >= 0)
			sum += n1[i] - '0';
		if (j >= 0)
			sum += n2[j] - '0';
		if (k >= size_r - 1)
			return (0);
		r[k] = (sum % 10) + '0';
		sum /= 10;
		i--;
		j--;
		k++;
	}
	r[k] = '\0';
	for (l = 0; l < k / 2; l++)
	{
		tmp = r[l];
		r[l] = r[k - 1 - l];
		r[k - 1 - l] = tmp;
	}
	return (r);
}
