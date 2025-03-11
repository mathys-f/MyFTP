/*
** EPITECH PROJECT, 2025
** command.c
** File description:
** command.c
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "command.h"

static char *get_client_command(client_t *client)
{
    char buffer[1024] = {0};
    ssize_t nb_read = 0;
    char *command = NULL;

    nb_read = read(client->fd, buffer, 1024);
    if (nb_read == -1)
        return NULL;
    command = strdup(buffer);
    return command;
}

void handle_client_command(client_t *client)
{
    char *command = get_client_command(client);
    char **args = my_str_to_word_array(command, " \t\n");
}
