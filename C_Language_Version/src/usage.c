/*
** generate_bare_repo
** File description:
** usage.c
*/

#include "my.h"

/* Original Usage

int main(int ac, char **av)
{
    printf("\t\t\t\t\t\x1b[1;93mUSAGE\x1b[0m\n");
    printf("The generate_bare_repo binary is an interactive script that ");
    printf("generates a bare repository.\nThe script Will ask questions and ");
    printf("you're expected to answer.\nIn the continuation of this usage, I");
    printf(" will explain each question asked by the script.\n\n\n");
    printf("\x1b[3;35mEnter your project's repository name:\x1b[0m\n");
    printf("You must write your desired bare repository name \x1b[2;30mand also the path\x1b[0m when encountering this question\n\n");
    printf("\x1b[3;31mEnter your deployment repository name:\x1b[0m\n");
    printf("You are asked to write the name \x1b[2;30mand also the path\x1b[0m of the deployment repository ");
    printf("that'll be on the same machine as the bare repository\n\n");
    printf("\x1b[3;36mWould you like to set CI/CD? (Yes/No)...\x1b[0m\n");
    printf("If answered \"yes\", this will set a post-receive hook that'll ");
    printf("automatically perform a \x1b[4;37mgit pull\x1b[0m in the ");
    printf("deployment repository and start the program in the repository.\n");
    printf("\x1b[1;91mThe repository must have a Makefile!!!\x1b[0m\n\n");
    printf("If answered \"no\", the deploy repository will be immediately created.\n");
};

*/

/* AI amplificated Usage. */

void usage(void)
{
    puts("\t\t\t\t\t\x1b[1;93mUSAGE\x1b[0m\n");
    printf("The generate_bare_repo binary is an interactive script that ");
    printf("generates a bare repository.\nThe script Will ask questions and ");
    printf("you're expected to answer.\nIn the continuation of this usage, I");
    puts(" will explain each question asked by the script.\n\n");
    puts("\x1b[3;35mEnter your project's repository name:\x1b[0m");
    puts("You will be prompted to provide a name for your bare repository. This name");
    puts("should reflect the purpose or identity of your project. Additionally, you must");
    puts("specify the desired file path where the repository will be created. For example, you might enter");
    puts("\x1b[2;30/path/to/repositories/my_project.git\x1b[0m\n");
    puts("\x1b[3;31mEnter your deployment repository name:\x1b[0m");
    puts("In this step, you will need to specify the name and path for the deployment");
    puts("repository. This repository will reside on the same machine as the bare repository.");
    puts("The deployment repository is where your application will be deployed and run.");
    puts("Ensure that the path is accessible and that the naming convention is consistent");
    puts("with your project's requirements. For instance, you might enter");
    puts("\x1b[3,31m/path/to/deployment/my_project\x1b[0m\n");
    puts("  ⚫ Here, you are given the option to configure Continuous Integration/Continuous");
    puts("Deployment (CI/CD) for your project.");
    puts("\t⦿ If you choose \"Yes\", the script will create a post-receive hook in the bare");
    puts("\t  repository. This hook will automate the deployment process by executing a");
    puts("\t  git pull in the deployment repository whenever changes are pushed to");
    puts("\t  the bare repository.");
    printf("⛔⚠️ \x1b[1;91mPlease note that for this functionality to work correctly,");
    printf("your deployment repository must contain a Makefile, as this will be used to");
    printf(" start the program after each deployment.\x1b[0m\n");
    puts("\t⦿ If you respond with \"No\", the script will proceed to create the deployment");
    puts("\t  repository without setting up the CI/CD process. This option is suitable if you");
    puts("\t  prefer to handle deployments manually or use a different deployment");
    puts("\t  strategy.");
    exit(0);
};
