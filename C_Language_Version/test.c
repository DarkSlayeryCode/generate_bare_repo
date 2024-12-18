#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void hide_norm_and_exec(char *str)
{
    int l = 0;
    int dev_null = open("/dev/null", O_WRONLY);

    if (dev_null == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        close(dev_null);
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        dup2(dev_null, STDOUT_FILENO);
        close(dev_null);
        exit(system(str));
    }
}

int main(int ac, char **av) {
    int l = 0;
    int dev_null = open("/dev/null", O_WRONLY);
    if (dev_null == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        close(dev_null);
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        dup2(dev_null, STDOUT_FILENO);
        close(dev_null);
        exit(system(av[1]));
    }
}
