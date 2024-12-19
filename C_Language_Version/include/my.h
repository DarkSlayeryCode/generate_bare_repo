/*
** generate_bare_repo (C Language Version)
** File description:
** my.h
*/

#ifndef MY_H_
    #define MY_H_
    #include <pwd.h>
    #include <fcntl.h>
    #include <stdio.h>
    #include <dirent.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <stdbool.h>
    #include <sys/stat.h>
    #include <sys/types.h>

typedef struct {
    int i;
    int j;
    int k;
} init_t;

typedef struct {
    char *name;
    char *exec_name;
} sfm_t;

typedef struct {
    char *sfm;
    char *git;
    char *make;
} download_with_t;

extern sfm_t sfm; /* Software Package Manager\
 (The command to download things ex: dnf, apt ...etc) */
extern char **environ;
extern char pwd[2000];
extern char response[5];
extern char *known_distr[];
extern char repo_name[2000];
extern bool is_already_filled;
extern char branch_name[2000];
extern char deploy_name[2500];
extern download_with_t dspt[];
extern void (*cut_script[])(void);

void usage(void);
void get_pbip(void);
char *my_whoami(void);
char **bin_array(void);
void repos_names(void);
int my_strlen(char *str);
char *cleanstr(char *src);
void create_app(char **av);
void lower_str(char str[]);
void reset_string(char str[]);
char **free_array(char **array);
char **to_array(char *str, char *c);
bool my_strstr(char *string, char *to_find);
char *get_command(char **arr, char *command);
int count_nb_chars(char *str, char *separator);
char **str_to_array(char *str, char *separator);
void execute_commands(char *command, char **arr);
void get_users_request(char str[], char *display, bool low);

#endif /* MY_H_ */
