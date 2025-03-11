/*
** EPITECH PROJECT, 2025
** command.c
** File description:
** command.c
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "command.h"

static const command_t commands[] = {
    {"QUIT", &quit},
    {NULL, NULL}
};

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

    if (args == NULL)
        return;
    for (int i = 0; commands[i].name; i++) {
        if (strcmp(commands[i].name, args[0]) == 0) {
            commands[i].func(NULL, client, args);
            break;
        }
    }
    free(command);
    for (int i = 0; args[i]; i++)
        free(args[i]);
    free(args);
}
