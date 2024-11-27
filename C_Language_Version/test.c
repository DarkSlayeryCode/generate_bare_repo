// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>

// extern char **environ;

// int main(int ac, char **av)
// {
//     char *arr[4];
//     arr[0] = "git";
//     arr[1] = "init";
//     arr[2] = "--bare";
//     arr[3] = NULL;
//     if (execve("/usr/bin/git", arr, environ) == -1) {
//         for (int i = 0; environ[i] != NULL; i++)
//             printf("%s\n", environ[i]);
//     }
// }

#include <string.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    char str1[] = "papa";
    char *str2 = strdup(str1);
    char *str3 = str2;
    free(str3);
}