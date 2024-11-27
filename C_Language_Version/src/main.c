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
            printf("%s\n", sfm.name);
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

char *getpwd(void)
{
    int i = 0;

    while (environ[i] != NULL && strncmp(environ[i], "PWD=", 4) != 0)
        i++;
    return &environ[i][4];
}

int main(void)
{
    int pos = 0;
    char *temp = NULL;

    get_sfm();
    char git_bash_actions[3000];
    strcpy(pwd, getpwd());
    pos = dep_com_where();
    if (get_command(bin_array(), "git") == NULL) {
        printf("git is not installed. Attempting to install git!!!\n");
        execute_commands(sfm.exec_name, str_to_array(dspt[pos].git, " "));
    }
    get_users_request(repo_name, "Enter your project's repository name:\n", false);
    while (1) {
        if (my_strlen(repo_name) == 0) {
            reset_string(repo_name);
            get_users_request(repo_name, "Project's repository name cannot be empty\n", false);
        } else
            break;
    }
    get_users_request(deploy_name, "Enter your deployment repository name:\n", false);
    if (my_strlen(deploy_name) == 0) {
        printf("Using the default deployment repository name since it was not provided!\n");
        strcpy(deploy_name, "deployment/");
        strcat(deploy_name, repo_name);
    }
    if (get_command(bin_array(), "make") == NULL) {
        printf("make is not installed. Attempting to install make!!!\n");
        execute_commands(sfm.exec_name, str_to_array(dspt[pos].make, " "));
    }
    if (mkdir(repo_name, 0751) == -1) {
        perror(NULL);
        exit(-42);
    }
    chdir(repo_name);
    temp = get_command(bin_array(), "git");
    execute_commands(temp, str_to_array("git init --bare", " "));
    sleep(1);
    get_users_request(response, "Would you like to set CI/CD?\n(Yes/No)...\n", true);
    while (1) {
            if (my_strlen(response) == 1 && response[0] == 'y' || response[0] == 'n')
                break;
            if (strcmp(response, "yes") == 0 || strcmp(response, "no") == 0)
                break;
        reset_string(response);
        get_users_request(response, "The response can either be \"Yes\" or \"No\"\n", true);
    }
    if (response[0] == 'n') {
        char re[200];
        strcpy(git_bash_actions, "git clone ");
        strcat(git_bash_actions, getcwd(re, 200));
        strcat(git_bash_actions, " ");
        strcat(git_bash_actions, deploy_name);
        execute_commands(temp, str_to_array(git_bash_actions, " "));
    } else {
        get_users_request(branch_name, "On Which branch Would you like to set the hooks ?\n", false);
        if (my_strlen(branch_name) == 0)
            strcpy(branch_name, "master");
        chdir("hooks");
        FILE *post_receive = fopen("post-receive", "a");
        fprintf(post_receive, "#!/bin/bash\n\npath_bare_dir=$(pwd)\n");
        fprintf(post_receive, "if [ ! -d %s ]; then\n", deploy_name);
        fprintf(post_receive, "\tgit clone $path_bare_dir %s\n", deploy_name);
        fprintf(post_receive, "else\n\twhile read oldrev newrev ref\n\tdo\n");
        fprintf(post_receive, "\t\tif [[ $ref =~ .*/%s$ ]]; then\n", branch_name);
        fprintf(post_receive, "\t\t\techo \"Master ref received.  Deploying master branch to production...\"\n");
        fprintf(post_receive, "\t\t\tif ! git branch --list \"%s\" > /dev/null; then\n", branch_name);
        fprintf(post_receive, "\t\t\t\tgit --work-tree=%s --git-dir=%s/%s checkout -b %s\n", deploy_name, pwd, repo_name, branch_name);
        fprintf(post_receive, "\t\t\telse\n\t\t\t\tgit --work-tree=%s --git-dir=%s/%s checkout %s -f\n", deploy_name, pwd, repo_name, branch_name);
        fprintf(post_receive, "\t\t\tfi\n\t\telse\n");
        fprintf(post_receive, "\t\t\techo \"Ref $ref successfully received.  Doing nothing: only the master branch may be deployed on this server.\"\n");
        fprintf(post_receive, "\t\tfi\n\tdone\nfi\ncd %s\necho -e \"You must have a Makefile in your deployment repository!\"\n", deploy_name);
        fprintf(post_receive, "make\nif [ $? -ne 0 ]; then\n\techo \"There is no Makefile\"\nfi\n\n");
        fclose(post_receive);
        chmod("post-receive", S_IRWXU | S_IRWXO | S_IRWXG);
        printf("paste 'git clone %s@", my_whoami());
        get_pbip();
        printf(":%s/%s' in your terminal\n", pwd, repo_name);
    }
}
