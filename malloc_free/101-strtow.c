#include "main.h"
#include <stdlib.h>

/**
 * count_words - Helper function to count words in a string.
 * @str: String to evaluate.
 *
 * Return: Number of words.
 */
static int count_words(char *str)
{
	int count = 0, in_word = 0;

	while (*str)
	{
		if (*str == ' ')
		{
			in_word = 0;
		}
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

/**
 * free_words - Helper function to free allocated words.
 * @words: Array of strings.
 * @i: Number of elements to free.
 */
static void free_words(char **words, int i)
{
	while (i >= 0)
	{
		free(words[i]);
		i--;
	}
	free(words);
}

/**
 * strtow - Splits a string into words.
 * @str: String to split.
 *
 * Return: Pointer to array of strings (words), or NULL on failure/empty.
 */
char **strtow(char *str)
{
	char **words;
	int i = 0, j, len, num_words;

	if (str == NULL || *str == '\0')
		return (NULL);

	num_words = count_words(str);
	if (num_words == 0)
		return (NULL);

	words = malloc(sizeof(char *) * (num_words + 1));
	if (words == NULL)
		return (NULL);

	while (*str && i < num_words)
	{
		while (*str && *str == ' ')
			str++;

		len = 0;
		while (str[len] && str[len] != ' ')
			len++;

		words[i] = malloc(sizeof(char) * (len + 1));
		if (words[i] == NULL)
		{
			free_words(words, i - 1);
			return (NULL);
		}

		for (j = 0; j < len; j++)
			words[i][j] = str[j];
		words[i][j] = '\0';

		str += len;
		i++;
	}
	words[i] = NULL;

	return (words);
}
