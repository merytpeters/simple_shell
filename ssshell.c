#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"
#define BUFFER_SIZE 1024

/**
 * interactive_mode - This mode is activated when the program is called with no
 * arguments of command piped to it
 *
 * @env: This is the array of environment variables
 * @av: Argument variable the program was called with
 *
 * Return: 1 always
 */

int interactive_mode(char **av, char **env)
{
	int keep_running = 1;
	char *command = NULL;
	size_t n = 0;
	ssize_t nread;

	while (keep_running == 1)
	{
		command = NULL;
		printf("($) ");
		fflush(stdout);
		nread = _getline(&command, &n, stdin);
		if (nread == -1)
		{
			return (-1);
		}
		rmv_nwline(command);
		executioner(command, av, env);
		free(command);
	}
	return (1);
}

/**
 * non_interactive_mode - This mode is activated if a command
 * is piped into the program
 *
 * @env: The environment variables to use
 * @av: The argument variables the program was called with
 *
 * Return: 1 always
 */

int non_interactive_mode(char **av, char **env)
{
	ssize_t nread;
	size_t n = 0;
	char *buffer = NULL;


	while ((nread = _getline(&buffer, &n, stdin)) > 0)
	{
		executioner(buffer, av, env);
		free(buffer);
		buffer = NULL;
	}
	free(buffer);
	return (1);

}

/**
 * file_input_mode - This mode is activated if a file was sent to the program
 *
 * @filename: The name of the file
 * @av: The terminal args program was invoked with
 * @env: list of environment variables
 *
 * Return: 1 on success
 */

int file_input_mode(char *filename, char **av, char **env)
{
	FILE *file_stream;
	ssize_t nread;
	size_t n = 128;
	char *buffer = NULL;

	file_stream = fopen(filename, "r");
	if (file_stream == NULL)
	{
		fprintf(stderr, "Error: Unable to open file\n");
		return (0);
	}
	else
	{
		while ((nread = _getline(&buffer, &n, file_stream)) != -1)
		{
			rmv_nwline(buffer);
			executioner(buffer, av, env);
		}
		free(buffer);
	}
	if (ferror(file_stream))
	{
		perror("Error reading from file");
		return (0);
	}
	return (1);
}

/**
 * main - The entry point of the shell program
 *
 * @ac: Number of arguments this program was invoked with
 * @av: Array of arguments in strings that this program was invoked with
 * @env: Array of environment variables
 *
 * Return: 0 on success always
 */

int main(int ac, char **av, char **env)
{
	int is_terminal;

	is_terminal = isatty(STDIN_FILENO);
	/* Non-interactive Mode */
	if (is_terminal == 0)
	{
		non_interactive_mode(av, env);
	}
	else
	{
		if (ac == 2)
		{
			/* File input mode */
			file_input_mode(av[1], av, env);
		}
		else
		{
			/* interactive mode */
			interactive_mode(av, env);
		}
	}
	return (0);
}
