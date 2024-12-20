/*
** generate_bare_repo (C language Version)
** File description:
** get_bins_path.c
*/

#include "my.h"

char **bin_array(void)
{
    int i = 0;
    char **arr = NULL;

    while (environ[i] != NULL && strncmp(environ[i], "PATH=", 5) != 0)
        i++;
    arr = str_to_array(&environ[i][5], ":");
    return arr;
}

char *get_command(char **arr, char *command)
{
    int i = 0;
    char str[100];
    char *s = NULL;

    while (arr[i] != NULL) {
        strcpy(str, arr[i]);
        strcat(str, "/");
        s = strdup(strcat(str, command));
        if (access(s, F_OK) == 0) {
            free_array(arr);
            return s;
        }
        reset_string(str);
        free(s);
        i++;
    }
    free_array(arr);
    return NULL;
}

void execute_commands(char *command, char **arr)
{
    int fork_return = fork();

    if (fork_return == 0) {
        if (execve(command, arr, environ) == -1) {
            printf("An error occurred, ");
            printf("couldn't proceed with the generation.\n");
            exit(-10);
        }
        exit(0);
    }
    free_array(arr);
    if (fork_return == -10) {
        printf("Terminating...\n");
        exit(-42);
    }
}
