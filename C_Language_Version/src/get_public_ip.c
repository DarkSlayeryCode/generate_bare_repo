/*
** generate_bare_repo
** File description:
** get_public_ip.c
*/

#include "my.h"

void get_pbip(void)
{
    FILE *fp;
    char buffer[128];

    fp = popen("curl -s ipinfo.io/ip", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        return;
    }
    fgets(buffer, sizeof(buffer), fp);
    printf("%s", buffer);
    pclose(fp);
    return;
}
