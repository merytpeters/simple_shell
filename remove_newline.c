#include "main.h"

/**
 * rmv_nwline - This function takes in a string and removes any newline present
 *
 * @str: The string we want to remove the newline from
 */

void rmv_nwline(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
}

