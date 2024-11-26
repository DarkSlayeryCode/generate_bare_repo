/*
** generate_bare_repo (C Language Version)
** File description:
** cleanstr.c
*/

#include "my.h"

static int i;
static int j;
static char *destptr;
static char dest[5000];

int check_char(char c)
{
    return (c == ' ' || c == '\t' || c == '\n') ? 1 : 0;
}

char *cleanstr(char *src)
{
    i = 0;
    j = 0;
    destptr = NULL;
    while (check_char(src[i]) == 1)
        i++;
    while (src[i] != '\0') {
        if (check_char(src[i]) == 1 && check_char(src[i - 1]) == 1) {
            i++;
            continue;
        }
        if (check_char(src[i]) == 1 && src[i + 1] == '\0')
            break;
        dest[j] = src[i];
        j++;
        i++;
    }
    dest[j] = '\0';
    dest[j - 1] = (check_char(dest[j - 1]) == 1) ? '\0' : dest[j - 1];
    destptr = dest;
    return destptr;
}
