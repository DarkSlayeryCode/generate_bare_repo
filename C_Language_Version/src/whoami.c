/*
** EPITECH PROJECT, 2024
** generate_bare_repo
** File description:
** whoami.c
*/

#include "my.h"

char *my_whoami(void)
{
    int uid = getuid();
    struct passwd *pw = getpwuid(uid);

    if (pw)
        return pw->pw_name;
    return "";
}