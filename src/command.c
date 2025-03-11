/*
** EPITECH PROJECT, 2025
** command.c
** File description:
** command.c
*/

#include <unistd.h>

#include "command.h"

static char *get_client_command(client_t *client)
{
    char buffer[1024] = {0};
    ssize_t nb_read = 0;
    char *command = NULL;

    nb_read = read(client->fd, buffer, 1024);
    command = strstr(buffer, "\r\n");
    if (command != NULL)
        command[0] = '\0';
    return command;
}

void handle_client_command(client_t *client)
{
    char *command = get_client_command(client);
}
