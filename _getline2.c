#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * _getline - A function to recieve input from the user
 *
 * @lineptr: The buffer to which we will save the entered chars
 * @n: The initial size of lineptr (malloced)
 * @stream: The stream we will get the input from
 * Return: The actual count of the number of chars entered
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t pos;
	int ch;

	if (*lineptr == NULL)
	{
		*n = 128;
		*lineptr = malloc(sizeof(char) * *n);
		if (*lineptr == NULL)
			return (-1);
	}
	pos = 0;
	while ((ch = fgetc(stream)) != EOF && ch != '\n')
	{
		(*lineptr)[pos++] = ch;
		if (pos >= (ssize_t)*n)
		{
			*n *= 2;
			*lineptr = realloc(*lineptr, *n);
			if (*lineptr == NULL)
				return (-1);
		}
	}
	if (pos == 0 && ch == EOF)
	{
		return (-1);
	}
	(*lineptr)[pos] = '\0';
	return (pos);
}
