#include "main.h"

/**
 * build_path - A function that adds the prefix to build an
 * absolute path to a command
 *
 * @path: The prefix to add to the command
 * @str: The command we need to add the prefix to
 * Return: The combination of this two
 */

char *build_path(char *path, char *str)
{
	unsigned int i = 0;
	unsigned int len1 = strlen(path);
	unsigned int len2 = strlen(str);
	char *new_path = NULL;

	new_path = malloc(sizeof(char) * len1 + len2 + 2);
	if (new_path)
	{
		for (i = 0; i < len1; i++)
		{
			new_path[i] = path[i];
		}
		new_path[i] = '/';
		for (i = len1 + 1; i < len1 + len2 + 1; i++)
		{
			new_path[i] = str[i - len1 - 1];
		}
		new_path[len1 + len2 + 1] = '\0';
	}
	return (new_path);
}

/**
 * path_builder - A function that checks if a relative command is valid and
 * constructs an absolute path to the command
 *
 * @paths_v: The paths we need to scan through for the command
 * @str: The relative command we need to find
 * Return: Either Null when the command is not found
 * or an absolute path to the command
 */

char *path_builder(char **paths_v, char *str)
{
	int j = 0;
	struct stat st;
	char *new_path;
	int path_fd;
	int fstat_status;

	while (paths_v[j] != NULL)
	{
		path_fd = open(paths_v[j], 16384);
		if (path_fd != -1)
		{
			fstat_status = fstatat(path_fd, str, &st, 0);
			if (fstat_status == 0)
			{
				close(path_fd);
				new_path = build_path(paths_v[j], str);
				return (new_path);
			}
			else
			{
				close(path_fd);
				j++;
				continue;
			}
		}
		j++;
	}
	return (NULL);
}

/**
 * validate_command - A function to check if a command entered is valid
 * end returns a path to it
 *
 * @str: The command we need to check for validity
 * @env: The environment variable array where we'll take the
 * PATH variable from
 * Return: A path to the command or NULL if it doesnt exist
 */

char *validate_command(char *str, char **env)
{
	struct stat st;
	char *paths;
	char *final_path;
	char **paths_v;
	int fstat_status;


	if (str[0] == '/')
	{
		fstat_status = stat(str, &st);
		if (fstat_status == 0)
		{
			final_path = strdup(str);
			return (final_path);
		}
		else
		{
			return (NULL);
		}
	}
	else
	{
		paths = _getenv("PATH", env);
		paths_v = _strtok(paths, ":");
		final_path = path_builder(paths_v, str);
		free_vec(paths_v);
		return (final_path);
	}
	return (NULL);
}

/**
 * is_builtin - A function to check if the entered command is a builtin
 *
 * @str: The command we want to check
 * Return: Either the command or NULL if it is valid or not
 */

char *is_builtin(char *str)
{
	char *custom_commands[] = {"exit", "alias", "cd", "setenv",
		"unsetenv", "env", NULL};
	int i;

	i = 0;
	while (custom_commands[i] != NULL)
	{
		if (strcmp(str, custom_commands[i]) == 0)
		{
			return (str);
		}
		i++;
	}
	return (NULL);
}

/**
 * run_builtin - A function to execute a builtin command that has been found
 * @args: The arrays of arguments
 * @env: The array of environment variables
 */

void run_builtin(char **args, char **env)
{
	char *custom_commands[] = {"exit",
		"alias",
		"cd",
		"setenv",
		"unsetenv",
		"env",
		NULL};
	void (*custom_command_fns[])(char **av, char **env) = {custom_exit,
		make_alias,
		change_directory,
		set_env,
		unset_env,
		env_view};
	int i;

	i = 0;
	for (i = 0; custom_commands[i] != NULL; i++)
	{
		if (strcmp(args[0], custom_commands[i]) == 0)
		{
			custom_command_fns[i](args, env);
			break;
		}
	}
}
