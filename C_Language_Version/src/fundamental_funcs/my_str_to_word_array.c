/*
** generate_bare_repo (C Language Version)
** File description:
** my_str_to_word_array.c
*/

#include "my.h"

static char **arr;
static init_t l = {0, 0, 0};

char **free_array(char **array)
{
    int i = 0;

    if (array == NULL)
        return NULL;
    while (array[i] != NULL) {
        free(array[i]);
        i++;
    }
    free(array);
    return NULL;
}

bool is_separator(char c, char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == c)
            return true;
        i++;
    }
    return false;
}

int count_nb_chars(char *str, char *separator)
{
    int counter = 1;

    while (*str != '\0') {
        counter += (is_separator(*str, separator) == true) ? 1 : 0;
        *str++;
    }
    return counter;
}

static int count_till_next_char(char *str, char *separator)
{
    int i = 0;

    while (is_separator(str[i], separator) == false && str[i] != '\0')
        i++;
    return i;
}

static void cut_str_to_word_array(char *str, char *separator)
{
    arr = malloc(sizeof(char *) * count_nb_chars(str, separator) + 8);
    arr[0] = malloc(sizeof(char) *(count_till_next_char(str, separator))
    + my_strlen(separator) + 8);
    while (str[l.i] != '\0') {
        if (is_separator(str[l.i], separator) == false) {
            arr[l.j][l.k] = str[l.i];
            l.k++;
        }
        if (l.i > 0 && is_separator(str[l.i - 1], separator) == false &&
        is_separator(str[l.i], separator) == true) {
            arr[l.j][l.k] = '\0';
            l.j++;
            l.k = 0;
            arr[l.j] = malloc(sizeof(char) *
            count_till_next_char(&str[l.i + 1], separator)
            + my_strlen(separator) + 8);
        }
        l.i++;
    }
    return;
}

char **str_to_array(char *str, char *separator)
{
    arr = NULL;
    l = (init_t){0, 0, 0};
    cut_str_to_word_array(str, separator);
    arr[l.j][l.k] = '\0';
    if (arr[l.j][0] == '\0')
        arr[l.j] = NULL;
    else
        arr[l.j + 1] = NULL;
    return arr;
}
