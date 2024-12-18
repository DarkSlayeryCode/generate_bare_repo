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
char branch_name[2000];
char deploy_name[2500];
bool is_already_filled;

static void get_sfm(void)
{
    char *s;

    for (int i = 0; known_distr[i] != NULL; i++) {
        s = get_command(bin_array(), known_distr[i]);
        if (s != NULL) {
            sfm = (sfm_t){known_distr[i], s};
            free(s);
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
    if (ac < 2 || ac > 3) {
        printf("Copy \"%s create-app [name] \"\n\tor\n", av[0]);
        printf("\"%s create-repo [name] \"\n", av[0]);
        printf("Name is not mandatory\n");
        exit (-42);
    }
    is_already_filled = false;
    for (int i = 1; av[i] != NULL && i < 2; i++)
        lower_str(av[i]);
    if (ac == 2) {
        if (strcmp(av[1], "-h") == 0 || strcmp(av[1], "-help") == 0
        || strcmp(av[1], "--help") == 0)
            usage();
    }
    if (strcmp(av[1], "create-app") != 0 && strcmp(av[1], "create-repo") != 0) {
        printf("Copy \"%s create-app [name] \"\n\tor\n", av[0]);
        printf("\"%s create-repo [name] \"\n", av[0]);
        printf("Name is not mandatory\n");
        exit(-42);
    }
    if (ac == 3) {
        strcpy(repo_name, av[2]);
        is_already_filled = true;
    }
    get_sfm();
    if (strcmp(av[1], "create-repo") == 0) {
        strcpy(pwd, getpwd());
        cut_script[0]();
        cut_script[1]();
        cut_script[2]();
        cut_script[4]();
    } else {
        DIR *app_dir = NULL;
        char commands[500];
        char root_docu[100];
        int config_file = 0;
        char proxy_pass[100];
        char domain_name[100];
        char server_alias[120];
        char config_file_name[110];

        if (geteuid() != 0) {
            printf("You need to run as root to use this option\n");
            printf("Copy \"sudo %s create-app\" in your terminal\n", av[0]);
            exit(1);
        }
        if (is_already_filled == false)
            get_users_request(domain_name, "Enter Domain Name:\n", false);
        else
            strcpy(domain_name, av[2]);
        strcpy(config_file_name, domain_name);
        strcat(config_file_name, ".conf");
        strcpy(server_alias, "www.");
        strcat(server_alias, domain_name);
        get_users_request(response, "Would you like to set Reverse Proxy Deployment? (y/n)\n", true);
        while (1) {
                if (my_strlen(response) == 1 && response[0] == 'y' || response[0] == 'n')
                    break;
                if (strcmp(response, "yes") == 0 || strcmp(response, "no") == 0)
                    break;
            reset_string(response);
            get_users_request(response, "The response can either be \"Yes\" or \"No\"\n", true);
        }
        if (response[0] == 'y')
            get_users_request(proxy_pass, "Enter Proxy's domain:\n", false);
        else
            get_users_request(root_docu, "Enter Root document:\n", false);
        app_dir = opendir("/etc/apache2/");
        if (app_dir == NULL) {
            if (mkdir("/etc/apache2/", 0777) == -1) {
                perror(NULL);
            exit(-42);
            }
        }
        if (chdir("/etc/apache2/") == -1) {
            perror(NULL);
            exit(-42);
        }
        closedir(app_dir);
        app_dir = opendir("sites-available");
        if (app_dir == NULL) {
            if (mkdir("sites-available", 0777) == -1) {
                perror(NULL);
            exit(-42);
            }
        }
        if (chdir("sites-available") == -1) {
            perror(NULL);
            exit(-42);
        }
        closedir(app_dir);
        config_file = open(config_file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (config_file <= 0) {
            close(config_file);
            printf("Failed to create %s\n", config_file_name);
            exit(-42);
        }
        dprintf(config_file, "<VirtualHost *:80>\n\tServerName ");
        dprintf(config_file, "%s\n\tServerAlias %s\n", domain_name, server_alias);
        dprintf(config_file, "\n\n\tserverAdmin webmaster@localhost\n");
        if (response[0] == 'n') {
            dprintf(config_file, "\tDocumentRoot %s\n", root_docu);
            dprintf(config_file, "<Directory %s>\n", root_docu);
            dprintf(config_file, "\tOptions Indexes FollowSymLinks MultiViews\n");
            dprintf(config_file, "\tAllowOverride all\n\tRequire all granted\n\t");
            dprintf(config_file, "Order allow,deny\n\tallow from all\n\n\t");
            dprintf(config_file, "<IfModule mod_rewrite.c>\n\t\tRewriteEngine On\n");
            dprintf(config_file, "\t\tRewriteBase /\n\t\tRewriteRule ^index\\.html$ - [L]\n");
            dprintf(config_file, "\t\tRewriteCond %%{REQUEST_FILENAME} !-f\n");
            dprintf(config_file, "\t\tRewriteCond %%{REQUEST_FILENAME} !-d\n");
            dprintf(config_file, "\t\tRewriteRule . /index.html [L]\n");
            dprintf(config_file, "\t</IfModule>\n</Directory>\n");
        } else {
            dprintf(config_file, "\t\tProxyPass / %s\n", proxy_pass);
            dprintf(config_file, "\t\tProxyPassReverse / %s\n\n", proxy_pass);
        }
        dprintf(config_file, "\t\tErrorLog ${APACHE_LOG_DIR}/error.log\n");
        dprintf(config_file, "\t\tCustomLog ${APACHE_LOG_DIR}/access.log combined");
        dprintf(config_file, "\n</VirtualHost>\n");
        close(config_file);
        strcpy(commands, "sudo a2ensite ");
        strcat(commands, config_file_name);
        system(commands);
        int s = dup(1);
        int dev_null = open("/dev/null", O_WRONLY);
        dup2(dev_null, 1);
        system("sudo -E a2enmod proxy");
        system("sudo -E a2enmod proxy_http");
        system("sudo -E a2enmod rewrite");
        if (system("sudo -E systemctl restart apache2") != 0)
            system("sudo -E systemctl start apache2.service");
        system("sudo -E systemctl reload apache2");
        strcpy(commands, "sudo -E certbot -d ");
        strcat(commands, domain_name);
        strcat(commands, " --apache");
        system(commands);
        close(dev_null);
        // dup2(s, 1);
        // close(s);
    }
    return 0;
}

/*
    export INSTA_USERNAME=new_gen_kondo
    env | grep INSTA
    export INSTA_PASSWORD=3rd_sushi
*/