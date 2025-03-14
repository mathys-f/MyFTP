/*
** EPITECH PROJECT, 2025
** pwd.c
** File description:
** pwd.c
*/

#include <unistd.h>
#include <string.h>

#include "loop.h"
#include "client.h"

void pwd(my_ftp_t *my_ftp, client_t *client, char **args)
{
    (void)my_ftp;
    (void)args;
    if (client->is_logged == false) {
        write(client->fd, "530 Not logged in.\r\n", 20);
        return;
    }
    write(client->fd, "257 \"", 5);
    write(client->fd, client->path, strlen(client->path));
    write(client->fd, "\" created.\r\n", 12);
}
