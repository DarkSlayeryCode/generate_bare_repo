// #include <string.h>
// #include <unistd.h>

#include <stdio.h>

int add(int x, int y)
{
    return x + y;
}

int substract(int x, int y)
{
    return x - y;
}

int multiply(int x, int y)
{
    return x * y;
}

int divide(int x, int y)
{
    return x / y;
}

int (*ptr_tab[])(int, int) = {
    add,
    substract,
    multiply,
    divide
};

int main()
{
    int x = 5;
    // x = +~x;
    printf("%d\n", ptr_tab[3](5, 2));
}

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

// #include <stdio.h>
// #include <stdlib.h>

// int main() {
//     FILE *fp;
//     char buffer[128];
//     fp = popen("curl -s ipinfo.io/ip", "r");
//     if (fp == NULL) {
//         printf("Failed to run command\n");
//         return 1;
//     }
//     fgets(buffer, sizeof(buffer), fp);
//     printf("%s", buffer);
//     pclose(fp);
//     return 0;
// }
