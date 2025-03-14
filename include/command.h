/*
** EPITECH PROJECT, 2025
** command.c
** File description:
** command.c
*/

#ifndef COMMAND_H
    #define COMMAND_H

    #include "client.h"

typedef struct command_s {
    char *name;
    void (*func)(my_ftp_t *my_ftp, client_t *client, char **args);
} command_t;

typedef struct command_help_s {
    char *name;
    char *desc;
    int len;
} command_help_t;

void user(my_ftp_t *my_ftp, client_t *client, char **args);
void pass(my_ftp_t *my_ftp, client_t *client, char **args);
void quit(my_ftp_t *my_ftp, client_t *client, char **args);
void help(my_ftp_t *my_ftp, client_t *client, char **args);
void noop(my_ftp_t *my_ftp, client_t *client, char **args);

void handle_client_command(my_ftp_t *my_ftp, int fd);
char **my_str_to_word_array(char *str, char *delimiters);

#endif /* !COMMAND_H */
