/*
** generate_bare_repo
** File description:
** create_app.c
*/

#include "my.h"

DIR *app_dir;
int config_file;
char commands[500];
char root_docu[100];
char proxy_pass[100];
char domain_name[100];
char server_alias[120];
char config_file_name[110];

void check_if_app_dir_exist(void)
{
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
}

void fill_config_file(void)
{
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
}

void exec_apache_commands(void)
{
    strcpy(commands, "sudo a2ensite ");
    strcat(commands, config_file_name);
    system(commands);
    system("sudo -E a2enmod proxy > /dev/null");
    system("sudo -E a2enmod proxy_http > /dev/null");
    system("sudo -E a2enmod rewrite > /dev/null");
    if (system("sudo -E systemctl restart apache2") != 0)
        system("sudo -E systemctl start apache2.service");
    system("sudo -E systemctl reload apache2");
    strcpy(commands, "sudo -E certbot -d ");
    strcat(commands, domain_name);
    strcat(commands, " --apache");
    system(commands);
}

void create_app(char **av)
{
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
    check_if_app_dir_exist();
    fill_config_file();
    exec_apache_commands();
}