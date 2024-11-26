/*
** generate_bare_repo (C Language Version)
** File description:
** main.c
*/

#include "my.h"

sfm_t sfm;
char requests[2000];
download_with_t dspt[] = {
    (download_with_t){"apt", "apt install git", "apt install make"},
    (download_with_t){"yum", "yum install git", "yum install make"},
    (download_with_t){"dnf", "dnf install git", "dnf install make"},
    (download_with_t){"zypper", "zypper install git", "zypper install make"},
    (download_with_t){"pacman", "pacman -S git", "pacman -S make"},
    (download_with_t){"emerge", "emerge git", "emerge make"},
    (download_with_t){"nix-env", "nix-env -iA nixpkgs.git", "nix-env -iA nixpkgs.make"},
    (download_with_t){"guix", "guix install git", "guix install make"},
    (download_with_t){"snap", "snap install git --classic", "apt install make"},
    (download_with_t){"flatpak", "snap install git --classic", "apt install make"},
    (download_with_t){"brew", "brew install git", "brew install make"},
    (download_with_t){NULL, NULL, NULL}
};

char *known_distr[] = {
    "apt",
    "dnf",
    "yum",
    "brew",
    "zypper",
    "pacman",
    "emerge",
    "nix-env",
    "guix",
    "rpm",
    "snap",
    "flatpak",
    NULL
};

void reset_string(char str[])
{
    int len = strlen(str);

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

static void get_sfm(void)
{
    char *s;

    for (int i = 0; known_distr[i] != NULL; i++) {
        s = get_command(bin_array(), known_distr[i]);
        if (s != NULL) {
            sfm = (sfm_t){known_distr[i], s};
            return;
        }
    }
    printf("Unknown Operating System\n");
    exit(-42);
}

int dep_com_where(void)
{
    int i = 0;

    for (; dspt[i].sfm != NULL; i++) {
        if (strcmp(dspt[i].sfm, sfm.name) == 0) 
            return i;
    }
    exit(-42);
}

int main(void)
{
    int pos = 0;

    get_sfm();
    pos = dep_com_where();
    if (get_command(bin_array(), "git") == NULL) {
        printf("git is not installed. Attempting to install git!!!\n");
        execute_commands(sfm.exec_name, str_to_array(dspt[pos].git, " "));
    }
    while (1) {
        get_users_request(requests, "Enter your project's repository name:");
        
    }
}
