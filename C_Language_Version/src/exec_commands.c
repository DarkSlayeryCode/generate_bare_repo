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
        s = strcat(str, command);
        if (access(s, F_OK) == 0) {
            free_array(arr);
            return s;
        }
        reset_string(str);
        i++;
    }
    free_array(arr);
    return NULL;
}

void execute_commands(char *command, char **arr)
{
    // char **arr = NULL;
    int fork_return = fork();

    if (fork_return == 0) {
        // arr = str_to_array(command, " ");
        if (execve(command, arr, environ) == -1) {
            printf("An error occurred, couldn't proceed with the generation.\n");
            exit(-10);
            // printf("Command \"%s\" not installed, attempting to install it!\n", command);
            // Installation command.
        }
        free_array(arr);
        exit(0);
    }
    if (fork_return == -10) {
        free_array(arr);
        printf("Terminating...\n");
        exit(-42);
    }
}
