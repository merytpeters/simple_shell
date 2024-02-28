#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024

void rmv_nwline(char *str);
char **_strtok(char *str, char *delim);
ssize_t _getline(char **str, size_t *n, FILE *stream);
char *_getenv(char *arg, char **env);
char *validate_command(char *str, char **env);

char *check_path(char *str);
char *make_string(char *str, int a, int b);

void enlarge_vector(char **vector);
void set_env(char **args, char **env);

void make_alias(char **args, char **env);
void change_directory(char **args, char **env);
void set_env(char **args, char **env);
void unset_env(char **args, char **env);
void env_view(char **args, char **env);
void custom_exit(char **args, char **env);

void executioner(char *buffer, char **av, char **env);

char *is_builtin(char *command);
void run_builtin(char **args, char **env);

void free_vec(char **vec);

#endif
