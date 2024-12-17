/*
** EPITECH PROJECT, 2024
** generate_bare_repo
** File description:
** init_tables.c
*/

#include "my.h"

download_with_t dspt[] = {
    (download_with_t){"apt", "sudo apt install git -y", "sudo apt install make -y"},
    (download_with_t){"yum", "sudo yum install git -y", "sudo yum install make -y"},
    (download_with_t){"dnf", "sudo dnf install git -y", "sudo dnf install make -y"},
    (download_with_t){"zypper", "zypper install git -y",
        "zypper install make -y"},
    (download_with_t){"pacman", "sudo pacman -S git -y", "sudo pacman -S make -y"},
    (download_with_t){"emerge", "sudo emerge git -y", "sudo emerge make -y"},
    (download_with_t){"nix-env", "sudo nix-env -iA nixpkgs.git -y",
        "sudo nix-env -iA nixpkgs.make -y"},
    (download_with_t){"guix", "sudo guix install git -y", "sudo guix install make -y"},
    (download_with_t){"snap", "sudo snap install git --classic -y",
        "sudo apt install make -y"},
    (download_with_t){"flatpak", "sudo snap install git --classic -y",
        "sudo apt install make -y"},
    (download_with_t){"brew", "sudo brew install git -y", "sudo brew install make -y"},
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
