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
#

#include "command.h"

static const command_t commands[] = {
    {"QUIT", &quit},
    {"USER", &user},
    {"PASS", &pass},
    {NULL, NULL}
};

static char *get_client_command(int fd)
{
    char *command = malloc(sizeof(char) * 256);
    int size = 0;
    ssize_t readed = 0;

    if (command == NULL)
        exit(84);
    while (1) {
        readed = read(fd, command + size, 256);
        if (readed == -1)
            exit(84);
        if (readed == 0)
            break;
        size += readed;
        if (size >= 2 && command[size - 2] == '\r' &&
            command[size - 1] == '\n') {
            command[size - 2] = '\0';
            break;
        }
    }
    return command;
}

void handle_client_command(my_ftp_t *my_ftp, int fd)
{
    char *command = get_client_command(fd);
    char **args = my_str_to_word_array(command, " \t");
    client_t *current = my_ftp->clients;

    if (args == NULL)
        return;
    while (current != NULL && current->fd != fd)
        current = current->next;
    for (int i = 0; commands[i].name != NULL; i++) {
        if (strcmp(commands[i].name, args[0]) == 0) {
            commands[i].func(my_ftp, current, args);
            break;
        }
    }
    free(command);
    for (int i = 0; args[i] != NULL; i++)
        free(args[i]);
    free(args);
}
