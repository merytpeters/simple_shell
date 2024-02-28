#include "main.h"

/**
 * run_command - A function that creates a process and runs a command
 *
 * @args: An argument array, list of strings
 * @env: The list of environment variables
 */

void run_command(char **args, char **env)
{
	pid_t child;
	int status;

	if (strcmp(args[0], "exit") == 0)
		exit(EXIT_FAILURE);
	child = fork();
	if (child == -1)
		return;
	if (child == 0)
	{
		if (execve(args[0], args, env) == -1)
			perror("Error:");
	}
	else
	{
		wait(&status);
	}
}

/**
 * executioner - A function that takes over from each mode after the
 * input has been collected
 *
 * @buffer: The input from the terminal or file
 * @av: The terminal arguments
 * @env: The environment variables
 */

void executioner(char *buffer, char **av, char **env)
{
	char **args;
	char **separated;
	char *valid_command;
	char *variable_replaced;
	static int count = 1;
	int i = 0;
	int j = 0;

	rmv_nwline(buffer);
	variable_replaced = check_path(buffer);
	free(buffer);
	separated = _strtok(variable_replaced, ";");
	free(variable_replaced);
	while (separated[i] != NULL)
	{
		args = _strtok(separated[i], " ");
		valid_command = validate_command(args[0], env);
		if (valid_command)
		{
			free(args[0]);
			args[0] = valid_command;
			printf("%s: ", av[0] + 2);
			fflush(stdout);
			run_command(args, env);
			for (j = 0; args[j] != NULL; j++)
				free(args[j]);
			free(args);
		}
		else if (is_builtin(args[0]))
		{
			run_builtin(args, env);
		}
		else
		{
			printf("%s: %d: %s: not found\n", av[0] + 2, count++, args[0]);
		}
		free(separated[i]);
		i++;
	}
	free(separated);
}
