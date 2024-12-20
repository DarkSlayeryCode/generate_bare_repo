/*
** generate_bare_repo
** File description:
** usage.c
*/

#include "my.h"

void usage(char *s)
{
    puts("\t\t\t\t\t\x1b[1;93mUSAGE\x1b[0m\n");
    printf("The %s binary has two sections:\n \x1b[1;94mcreate-repo\x1b[0m and \x1b[1;94mcreate-app\x1b[0m.\n", &s[2]);

    puts("\x1b[2;35mEnter your project's repository name:\x1b[0m");
    puts("Name and path, e.g., \x1b[2;30m/path/to/repositories/my_project.git\x1b[0m\n");

    puts("\x1b[2;31mEnter your deployment repository name:\x1b[0m");
    puts("Name and path, e.g., \x1b[2;31m/path/to/deployment/my_project\x1b[0m\n");

    puts("Configure CI/CD:");
    puts("\t\"Yes\" creates a post-receive hook.");
    puts("\t\"No\" sets up without CI/CD.\n");

    puts("\x1b[1;93mCreating an Application Configuration\x1b[0m\n");
    printf("The create-app section generates an Apache config file.\n");

    puts("\x1b[2;35mEnter Domain Name:\x1b[0m");
    puts("Provide the config file name, server name, and alias.\n");

    puts("\x1b[2;35mSet Reverse Proxy? (y/n):\x1b[0m\n");
    puts("\tif y\n \x1b[3;35mEnter Proxy's domain:\x1b[0m\nFills in the proxy details.\n");
    puts("\tif n\n \x1b[3;35mEnter Root document:\x1b[0m\nFills DocumentRoot.\n");
    exit(0);
}
