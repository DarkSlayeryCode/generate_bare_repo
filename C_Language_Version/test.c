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

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char buffer[128];
    fp = popen("curl -s ipinfo.io/ip", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return 1;
    }
    fgets(buffer, sizeof(buffer), fp);
    printf("%s", buffer);
    pclose(fp);
    return 0;
}
