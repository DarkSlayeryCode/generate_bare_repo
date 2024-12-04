/*
** EPITECH PROJECT, 2024
** generate_bare_repo
** File description:
** init_tables.c
*/

#include "my.h"

download_with_t dspt[] = {
    (download_with_t){"apt", "apt install git -y", "apt install make -y"},
    (download_with_t){"yum", "yum install git -y", "yum install make -y"},
    (download_with_t){"dnf", "dnf install git -y", "dnf install make -y"},
    (download_with_t){"zypper", "zypper install git -y",
        "zypper install make -y"},
    (download_with_t){"pacman", "pacman -S git -y", "pacman -S make -y"},
    (download_with_t){"emerge", "emerge git -y", "emerge make -y"},
    (download_with_t){"nix-env", "nix-env -iA nixpkgs.git -y",
        "nix-env -iA nixpkgs.make -y"},
    (download_with_t){"guix", "guix install git -y", "guix install make -y"},
    (download_with_t){"snap", "snap install git --classic -y",
        "apt install make -y"},
    (download_with_t){"flatpak", "snap install git --classic -y",
        "apt install make -y"},
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
