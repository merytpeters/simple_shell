#include "main.h"

/**
 * concat - A function to join a series of strings together
 *
 * @str1: The first string
 * @str2: The second string
 * @str3: The third string
 * Return: The joined string
 */

char *concat(char *str1, char *str2, char *str3)
{
	unsigned int len1;
	unsigned int len2;
	unsigned int len3;
	unsigned int i;
	char *new = NULL;

	len1 = strlen(str1);
	len2 = strlen(str2);
	len3 = strlen(str3);
	new = malloc(sizeof(char) * (len1 + len2 + len3 + 1));
	if (new != NULL)
	{
		for (i = 0; i < len1; i++)
			new[i] = str1[i];
		for (i = len1; i < len1 + len2; i++)
			new[i] = str2[i - len1];
		for (i = len1 + len2; i < len1 + len2 + len3; i++)
			new[i] = str3[i - (len1 + len2)];
		new[len1 + len2 + len3] = '\0';
	}
	free(str1);
	free(str3);
	return (new);
}

/**
 * check_path - A function to check if a string has variables
 *
 * @str: The string to check
 * Return: A new string
 */

char *check_path(char *str)
{
	int i = 0;
	char *substitute;
	char *first_half;
	char *next_half;

	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if ((strncmp(str + i + 1, "PATH", 4)) == 0)
			{
				substitute = getenv("PATH");
				next_half = make_string(str, i + 5, strlen(str));
				first_half = make_string(str, 0, i);
				return (concat(first_half, substitute, next_half));
			}
			else if ((strncmp(str + i + 1, "$", 1)) == 0)
			{
				substitute = getenv("PATH");
				next_half = make_string(str, i + 2, strlen(str));
				first_half = make_string(str, 0, i);
				return (concat(first_half, substitute, next_half));
			}
			else if ((strncmp(str + i + 1, "?", 1)) == 0)
			{
				substitute = getenv("PATH");
				next_half = make_string(str, i + 2, strlen(str));
				first_half = make_string(str, 0, i);
				return (concat(first_half, substitute, next_half));
			}
		}
		i++;
	}
	return (strdup(str));
}
