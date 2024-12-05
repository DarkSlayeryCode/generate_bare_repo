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
    if (my_strlen(to_find) > my_strlen(string))
        return false;
    while (string[i] != 0 && string[i] != to_find[j])
        i++;
    while (string[i] != 0 && string[i] == to_find[j]) {
        i++;
        j++;
    }
    if (to_find[j] == 0)
        return true;
    else
        my_strstr(&string[i], to_find);
}
