#include "main.h"

/**
 * custom_exit - A function to exit the shell if the user wants to
 *
 * @args: the commands the user entered into the terminal
 * @env: The list of environment variables
 */

void custom_exit(char **args, char **env)
{
	int status;
	(void)env;

	if (args[1] == NULL)
		_exit(0);
	status = atoi(args[1]);
	free_vec(args);
	_exit(status);
}

/**
 * make_alias - A function to allow the user create a custom alias
 *
 * @args: the commands the user entered into the terminal
 * @env: the list of environment variables
 */

void make_alias(char **args, char **env)
{
	(void)args;
	(void)env;
	printf("We are in alias\n");
}

/**
 * change_directory - A function that changes the disrectory of the process
 *
 * @args: the commands the user entered into the terminal
 * @env: The list of environment variables
 */

void change_directory(char **args, char **env)
{
	char *dir_returned;
	int chg_status;
	int err;
	char *destination;

	destination = args[1];
	if (destination == NULL || strcmp(destination, "~") == 0)
	{
		printf("%s\n", _getenv("HOME", env));
		chdir(_getenv("HOME", env));
	}
	else if (strcmp(destination, "-") == 0)
	{
		/* Set oldpwd to pwd */
		printf("%s\n", _getenv("HOME", env));
		chdir(_getenv("OLDPWD", env));
	}
	else if (destination[0] == '/')
	{
		chg_status = chdir(destination);
		err = errno;
		if (chg_status == -1)
		{
			printf("Cannot change directory with error: %d\n", err);
		}
	}
	else
	{
		dir_returned = _getenv("PWD", env);
		printf("%s\n", dir_returned);
	}
}

/**
 * set_env - A function to set the value of an environment variable
 *
 * @args: The commands the user entered into the terminal
 * @env: The list of environment variables
 */

void set_env(char **args, char **env)
{
	char *new_env = NULL;
	unsigned int i;

	(void)env;
	new_env = malloc(sizeof(char) * strlen(args[1]) + strlen(args[2]) + 2);
	if (new_env)
	{
		for (i = 0; i < strlen(args[1]); i++)
			new_env[i] = args[1][i];
		new_env[strlen(args[1])] = '=';
		for (i = 0; i < strlen(args[2]); i++)
			new_env[i + strlen(args[1]) + 1] = args[2][i];
		new_env[strlen(args[1]) + strlen(args[2]) + 1] = '\0';
		printf("New Env: %s\n", new_env);
	}
}

/**
 * unset_env - A function to unset the value of an environment variable
 *
 * @args: The commands the user entered into the terminal
 * @env: The list of environment variables
 */

void unset_env(char **args, char **env)
{
	(void)args;
	(void)env;
}
