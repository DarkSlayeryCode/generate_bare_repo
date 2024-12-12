/*
** generate_bare_repo (C Language Version)
** File description:
** main.c
*/

#include "my.h"

sfm_t sfm;
char pwd[2000];
char response[5];
char repo_name[2000];
bool is_already_filled;
char branch_name[2000];
char deploy_name[2500];

static void get_sfm(void)
{
    char *s;

    for (int i = 0; known_distr[i] != NULL; i++) {
        s = get_command(bin_array(), known_distr[i]);
        if (s != NULL) {
            sfm = (sfm_t){known_distr[i], s};
            free(s);
            return;
        }
    }
    printf("Unknown Operating System\n");
    exit(-42);
}

char *getpwd(void)
{
    int i = 0;

    while (environ[i] != NULL && strncmp(environ[i], "PWD=", 4) != 0)
        i++;
    return &environ[i][4];
}

int main(int ac, char **av)
{
    is_already_filled = false;
    if (ac != 2 && ac != 3 && ac != 4)
        exit -42;
    for (int i = 1; av[i] != NULL && i < 3; i++)
        lower_str(av[i]);
    if (ac == 2) {
        if (strcmp(av[1], "-h") == 0 || strcmp(av[1], "-help") == 0
        || strcmp(av[1], "--help") == 0)
            usage();
        exit(-42);
    }
    if (strcmp(av[1], "create") != 0) {
        puts("Error: The second parameter can only be \"create\"");
        exit(-42);
    }
    if (strcmp(av[2], "app") != 0 && strcmp(av[2], "repo") != 0) {
        puts("Error: The third parameter can either be \"app\" or \"repo\"");
        exit(-42);
    }
    if (ac == 4) {
        strcpy(repo_name, av[3]);
        is_already_filled = true;
    }
    if (strcmp(av[2], "repo") == 0) {
        get_sfm();
        strcpy(pwd, getpwd());
        cut_script[0]();
        cut_script[1]();
        cut_script[2]();
        cut_script[4]();
    } else {
        ;
    }
    return 0;
}
