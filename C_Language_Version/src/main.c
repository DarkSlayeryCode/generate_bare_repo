/*
** generate_bare_repo (C Language Version)
** File description:
** main.c
*/

#include "my.h"

sfm_t sfm;
char pwd[2000];
char response[5];
char repo_name[2000];
char deploy_name[2500];
char branch_name[2000];

download_with_t dspt[] = {
    (download_with_t){"apt", "apt install git -y", "apt install make -y"},
    (download_with_t){"yum", "yum install git -y", "yum install make -y"},
    (download_with_t){"dnf", "dnf install git -y", "dnf install make -y"},
    (download_with_t){"zypper", "zypper install git -y", "zypper install make -y"},
    (download_with_t){"pacman", "pacman -S git -y", "pacman -S make -y"},
    (download_with_t){"emerge", "emerge git -y", "emerge make -y"},
    (download_with_t){"nix-env", "nix-env -iA nixpkgs.git -y", "nix-env -iA nixpkgs.make -y"},
    (download_with_t){"guix", "guix install git -y", "guix install make -y"},
    (download_with_t){"snap", "snap install git --classic -y", "apt install make -y"},
    (download_with_t){"flatpak", "snap install git --classic -y", "apt install make -y"},
    (download_with_t){"brew", "brew install git -y", "brew install make -y"},
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

char *getpwd(void)
{
    int i = 0;

    while (environ[i] != NULL && strncmp(environ[i], "PWD=", 4) != 0)
        i++;
    return &environ[i][4];
}

int main(int ac, char **av)
{
    if (ac != 1 && ac != 2)
        exit -42;
    if (ac == 2) {
        lower_str(av[1]);
        if (strcmp(av[1], "-h") == 0 || strcmp(av[1], "-help") == 0
        || strcmp(av[1], "--help") == 0)
            usage();
        exit(-42);
    }
    get_sfm();
    strcpy(pwd, getpwd());
    cut_script[0]();
    cut_script[1]();
    cut_script[2]();
    cut_script[4]();
    return 0;
}
