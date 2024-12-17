#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void handler(int sig)
{
    write(1, "\n", 1);
    write(1, "my shell $> ", 12);
    // printf("\n");
    return;
}

int main(int ac, char **av)
{
    size_t n = 0;
    char *string;
    int status = 0;
    char *temp = NULL;

    signal(SIGINT, handler);
    while (1) {
        write(1, "my shell $> ", 12);
        if (getline(&string, &n, stdin) == -1) {
            write(1, "exit\n", 6);
            break;
        }
        temp = strdup(string);
        if (strcmp(strtok(temp, " \n\t"), "exit") == 0)
            break;
        free(temp);
        temp = NULL;
        status = system(string);
    }
    if (temp != NULL)
        free(temp);
    free(string);
    return status;
}