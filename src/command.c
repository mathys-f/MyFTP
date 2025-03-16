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
    {"USER", &user},
    {"PASS", &pass},
    {"QUIT", &quit},
    {"HELP", &help},
    {"NOOP", &noop},
    {"PWD", &pwd},
    {"CWD", &cwd},
    {NULL, NULL}
};

static void append_client_buffer(client_t *client, char *buffer)
{
    char *new_buffer = malloc(sizeof(char) * (strlen(client->buffer) +
        strlen(buffer) + 1));

    if (new_buffer == NULL)
        exit(84);
    strcpy(new_buffer, client->buffer);
    strcat(new_buffer, buffer);
    free(client->buffer);
    free(buffer);
    client->buffer = new_buffer;
}

static bool get_client_buffer(my_ftp_t *my_ftp, client_t *client, int fd)
{
    char *buffer = malloc(sizeof(char) * 256);
    ssize_t readed = 0;

    if (buffer == NULL)
        exit(84);
    readed = read(fd, buffer, 256);
    if (readed == -1 || readed == 0) {
        free(buffer);
        remove_client(my_ftp, fd);
        return false;
    }
    buffer[readed] = '\0';
    if (client->buffer != NULL)
        append_client_buffer(client, buffer);
    else
        client->buffer = buffer;
    return true;
}

static void get_args(my_ftp_t *my_ftp, client_t *current, char *command)
{
    char **args = my_str_to_word_array(command, " \t");
    bool is_command = false;

    if (args[0] == NULL) {
        free(args);
        return;
    }
    for (int i = 0; commands[i].name != NULL; i++) {
        if (strcmp(commands[i].name, args[0]) == 0) {
            commands[i].func(my_ftp, current, args);
            is_command = true;
            break;
        }
    }
    if (is_command == false)
        write(current->fd, "500 Unknown command.\r\n", 22);
    for (int i = 0; args[i] != NULL; i++)
        free(args[i]);
    free(args);
}

static void get_client_command(my_ftp_t *my_ftp, client_t *current)
{
    char *carriage_return = strstr(current->buffer, "\r\n");
    size_t len = 0;
    char *command = NULL;
    char *new_buffer = NULL;

    if (carriage_return == NULL)
        return;
    len = carriage_return - current->buffer;
    command = malloc(sizeof(char) * (len + 1));
    if (command == NULL)
        exit(84);
    strncpy(command, current->buffer, len);
    command[len] = '\0';
    new_buffer = strdup(carriage_return + 2);
    if (new_buffer == NULL)
        exit(84);
    free(current->buffer);
    current->buffer = new_buffer;
    get_args(my_ftp, current, command);
    free(command);
}

void handle_client_command(my_ftp_t *my_ftp, int fd)
{
    client_t *current = my_ftp->clients;

    while (current != NULL && current->fd != fd)
        current = current->next;
    if (get_client_buffer(my_ftp, current, fd) == false)
        return;
    get_client_command(my_ftp, current);
}
