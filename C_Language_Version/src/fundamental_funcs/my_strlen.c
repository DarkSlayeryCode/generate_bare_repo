/*
** EPITECH PROJECT, 2024
** generate_bare_repo
** File description:
** my_strlen.c
*/

#include "my.h"

int my_strlen(char *str)
{
    char *s;
    for (s = str; *s != 0; s++);
    return s - str;
}

/*

int my_strlen(char *str)
{
    int i = 0;

    if (str == NULL)
        return -1;
    for (; str[i] != 0; i++);
    return i;
}

*/