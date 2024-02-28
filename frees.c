#include "main.h"

/**
 * free_vec - A function that takes in an array of strings and frees them
 *
 * @vec: The array of strings to be freed
 */

void free_vec(char **vec)
{
	int i = 0;

	while (vec[i] != NULL)
		free(vec[i++]);
	free(vec);
}
