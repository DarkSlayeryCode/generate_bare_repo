/*
** generate_bare_repo
** File description:
** cut_script.c
*/

#include "my.h"

static int dep_com_where(void)
{
    int i = 0;

    for (; dspt[i].sfm != NULL; i++) {
        if (strcmp(dspt[i].sfm, sfm.name) == 0)
            return i;
    }
    exit(-42);
}

void repos_names(void)
{
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
    if (mkdir(repo_name, 0751) == -1) {
        perror(NULL);
        exit(-42);
    }
}

void check_dependencies(void)
{
    int pos = dep_com_where();

    if (get_command(bin_array(), "git") == NULL) {
        printf("git is not installed. Attempting to install git!!!\n");
        system(dspt[pos].make);
    }
    if (get_command(bin_array(), "make") == NULL) {
        printf("make is not installed. Attempting to install make!!!\n");
        system(dspt[pos].make);
    }
}

void set_deployment(void)
{
    char *temp = NULL;

    chdir(repo_name);
    temp = get_command(bin_array(), "git");
    system("git init --bare");
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
    free(temp);
    return;
}

void fill_post_receive(void)
{
    FILE *post_receive = fopen("post-receive", "a");

    fprintf(post_receive, "#!/bin/bash\n\npath_bare_dir=$(pwd)\n");
    fprintf(post_receive, "while read oldrev newrev ref\ndo\n");
    fprintf(post_receive, "\tif [[ $(echo \"$ref\" | sed 's|refs/heads/||') != %s ]]; then\n", branch_name);
    fprintf(post_receive, "\t\texit 1\n\tfi\n");
    fprintf(post_receive, "\techo \"Master ref received.  Deploying %s branch to production...\"\n", branch_name);
    fprintf(post_receive, "\tif [ ! -d %s ]; then\n\t\tgit clone $path_bare_dir %s\n\telse\n", deploy_name, deploy_name);
    fprintf(post_receive, "\t\tgit --work-tree=%s --git-dir=%s/%s checkout %s -f\n", deploy_name, pwd, repo_name, branch_name);
    fprintf(post_receive, "\tfi\ndone\ncd %s\n\n", deploy_name);
    fprintf(post_receive, "make\n");
    fprintf(post_receive, "if [ $? -ne 0 ]; then\n\techo \"There is no Makefile\"\nfi\n");
    fclose(post_receive);
    chmod("post-receive", S_IRWXU | S_IRWXO | S_IRWXG);
    return;
}

static void cut_create_deploy(char git_bash_actions[3000])
{
    char re[200];

    strcpy(git_bash_actions, "git clone ");
    strcat(git_bash_actions, getcwd(re, 200));
    strcat(git_bash_actions, " ");
    strcat(git_bash_actions, deploy_name);
    return;
}

static void temp_makefile(char *temp, char git_bash_actions[3000])
{
    char s[150];
    int default_makefile = 0;

    strcpy(git_bash_actions, pwd);
    strcat(git_bash_actions, "/");
    strcat(git_bash_actions, repo_name);
    while (my_strstr(s, deploy_name) == false) {
        chdir(deploy_name);
        getcwd(s, 150);
    }
    default_makefile = open("Makefile", O_RDWR | O_CREAT, 0644);
    dprintf(default_makefile, ".ONESHELL:\n");
    dprintf(default_makefile, "all:\n\techo \"Hello World!\"\n");
    close(default_makefile);
    system("git add Makefile");
    system("git commit -m \"Temporary Makefile.\"");
    system("git push");
    chdir(git_bash_actions);
}

void create_deploy_and_hook(void)
{
    char *temp = get_command(bin_array(), "git");
    char git_bash_actions[3000];

    cut_create_deploy(git_bash_actions);
    system(git_bash_actions);
    if (response[0] == 'y') {
        temp_makefile(temp, git_bash_actions);
        sleep(1);
        get_users_request(branch_name, "On Which branch Would you like to set the hooks ?\n", false);
        if (my_strlen(branch_name) == 0)
            strcpy(branch_name, "master");
        chdir("hooks");
        cut_script[3]();
        printf("paste 'git clone %s@", my_whoami());
        get_pbip();
        printf(":%s/%s' in your terminal\n", pwd, repo_name);
    }
    free(temp);
}

void (*cut_script[])(void) = {
    repos_names, /**/
    check_dependencies, /**/
    set_deployment, /**/
    fill_post_receive, /**/
    create_deploy_and_hook, /**/
    NULL
};
