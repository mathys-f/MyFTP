/*
** EPITECH PROJECT, 2025
** cdup.c
** File description:
** cdup.c
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#include "loop.h"
#include "client.h"

static char *get_path(char *current_directory, char *path)
{
    char *new_path = malloc(sizeof(char) * (strlen(current_directory) +
        strlen(path) + 2));

    if (new_path == NULL)
        exit(84);
    strcpy(new_path, current_directory);
    if (current_directory[strlen(current_directory) - 1] != '/')
        strcat(new_path, "/");
    strcat(new_path, path);
    return new_path;
}

static void check_path(client_t *client, char *path)
{
    char *real_path = realpath(path, NULL);

    if (real_path == NULL) {
        free(path);
        return;
    }
    free(path);
    free(client->path);
    client->path = real_path;
    write(client->fd, "250 Requested file action okay, completed.\r\n", 44);
}

void cdup(my_ftp_t *my_ftp, client_t *client, char **args)
{
    char *path = NULL;

    (void)my_ftp;
    (void)args;
    if (client->is_logged == false) {
        write(client->fd, "530 Not logged in.\r\n", 20);
        return;
    }
    path = get_path(client->path, "..");
    check_path(client, path);
}
