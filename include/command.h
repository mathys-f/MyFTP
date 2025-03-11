/*
** EPITECH PROJECT, 2025
** command.c
** File description:
** command.c
*/

#ifndef COMMAND_H
    #define COMMAND_H

    #include "client.h"

void handle_client_command(client_t *client);
char **my_str_to_word_array(char *str, char *delimiters);

#endif /* !COMMAND_H */
