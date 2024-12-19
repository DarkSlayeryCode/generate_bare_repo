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
char branch_name[2000];
char deploy_name[2500];
bool is_already_filled;

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
    if (ac < 2 || ac > 3) {
        printf("Copy \"%s create-app [name] \"\n\tor\n", av[0]);
        printf("\"%s create-repo [name] \"\n", av[0]);
        printf("Name is not mandatory\n");
        exit (-42);
    }
    is_already_filled = false;
    for (int i = 1; av[i] != NULL && i < 2; i++)
        lower_str(av[i]);
    if (ac == 2) {
        if (strcmp(av[1], "-h") == 0 || strcmp(av[1], "-help") == 0
        || strcmp(av[1], "--help") == 0)
            usage(av[0]);
    }
    if (strcmp(av[1], "create-app") != 0 && strcmp(av[1], "create-repo") != 0) {
        printf("Copy \"%s create-app [name] \"\n\tor\n", av[0]);
        printf("\"%s create-repo [name] \"\n", av[0]);
        printf("Name is not mandatory\n");
        exit(-42);
    }
    if (ac == 3) {
        strcpy(repo_name, av[2]);
        is_already_filled = true;
    }
    get_sfm();
    if (strcmp(av[1], "create-repo") == 0) {
        strcpy(pwd, getpwd());
        cut_script[0]();
        cut_script[1]();
        cut_script[2]();
        cut_script[4]();
    } else
        create_app(av);
    return 0;
}
