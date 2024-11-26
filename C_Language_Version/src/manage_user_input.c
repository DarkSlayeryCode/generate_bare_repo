/*
** generate_bare_repo
** File description:
** manage_user_input.c
*/

#include "my.h"

void reset_string(char str[])
{
    int len = my_strlen(str);

    for (int i = 0; i < len; i++)
        str[i] = 0;
    return;
}

void lower_str(char str[])
{
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] >= 65 && str[i] <= 90)
            str[i] += 32;
    }
    return;
}

void get_users_request(char str[], char *display)
{
    write(1, display, strlen(display));
    scanf("%s", str);
    lower_str(str);
    strcpy(str, cleanstr(str));
}