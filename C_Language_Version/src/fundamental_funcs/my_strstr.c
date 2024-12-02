/*
** generate_bare_repo (C Language Version)
** File description:
** my_strstr.c
*/

#include "my.h"

bool my_strstr(char *string, char *to_find)
{
    int i = 0;
    int j = 0;

    if (to_find == NULL || string == NULL)
        return false;
    if (strlen(to_find) > strlen(string))
        return false;
    if (string[0] != to_find[0])
        return false;
    while (string[i] != 0 && string[i] == to_find[j]) {
        i++;
        j++;
    }
    return (to_find[j] == 0) ? true : false;
}
