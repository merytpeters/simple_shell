#include "main.h"

/**
 * insert_string - A function to insert string
 *
 * @words: words
 * @word_count: word count
 * @str: str
 * @len: len
 * @start: start
 */

void insert_string(char ***words, size_t *word_count,
		char *str, size_t *len, size_t *start)
{
	char **words_temp;
	size_t j;

	words_temp = realloc(*words, (*word_count + 1) * sizeof(char *));
	if (words_temp == NULL)
	{
		free_vec(*words);
		return;
	}
	*words = words_temp;
	(*words)[*word_count] = malloc((*len + 1) * sizeof(char));
	if ((*words)[*word_count] == NULL)
	{
		for (j = 0; j < *word_count; j++)
			free((*words)[j]);
		free(*words);
		return;
	}
	strncpy((*words)[*word_count], &str[*start], *len);
	(*words)[*word_count][*len] = '\0';
}

/**
 * _strtok - A custom tokenizer
 *
 * @str: The string we want to tokenize
 * @delim: The delimiter by which we split the string
 * Return: An array of strings
 */

char **_strtok(char *str, char *delim)
{
	char **words = NULL;
	char **words_temp;
	size_t word_count = 0;
	size_t str_length = strlen(str);
	size_t len;
	size_t start = 0;
	size_t i;

	words = malloc(sizeof(char *));
	if (words == NULL)
		return (NULL);
	for (i = 0; i <= str_length; i++)
	{
		if (str[i] == '\0' || strchr(delim, str[i]) != NULL)
		{
			len = i - start;
			if (len > 0)
			{
				insert_string(&words, &word_count, str, &len, &start);
				word_count++;
			}
			start = i + 1;
		}
	}
	words_temp = realloc(words, (word_count + 1) * sizeof(char *));
	if (words_temp == NULL)
	{
		for (i = 0; i < word_count; i++)
		{
			free(words[i]);
		}
		free(words);
		return (NULL);
	}
	words = words_temp;
	words[word_count] = NULL;
	return (words);
}
