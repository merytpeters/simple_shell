#include <unistd.h>
#include <stdio.h>
#include <string.h>

/**
 * _getenv - A funtion to get the value of an environment variable
 *
 * @name: The name of the environment variable we want to find
 * @env: A list of environment variables passed in from main
 * Return: A pointer to the Value of the environment variable
 * Null if the variable is not fourd
 */

char *_getenv(const char *name, char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		if (strncmp(env[i], name, strlen(name)) == 0)
		{
			return (env[i] + strlen(name) + 1);
		}
		i++;
	}
	return (NULL);
}
