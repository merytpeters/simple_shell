#include "main.h"

/**
 * env_view - A function that displays the environment variable
 *
 * @args: The command the user entered to display the env
 * variable
 * @env: An array of environment variables maintained by the system
 */

void env_view(char **args, char **env)
{
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		if (strncmp(env[i], args[1], strlen(args[1])) == 0)
			printf("%s\n", env[i] + strlen(args[1]) + 1);
	}
}
