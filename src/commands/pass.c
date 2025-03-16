/*
** EPITECH PROJECT, 2025
** pass.c
** File description:
** pass.c
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "loop.h"
#include "client.h"

static bool check_anonymous(my_ftp_t *my_ftp, client_t *client, char **args)
{
    if (args[1] == NULL && strcmp(client->username, "Anonymous") == 0) {
        client->is_logged = true;
        client->password = strdup("");
        client->path = realpath(my_ftp->path, NULL);
        if (client->path == NULL)
            exit(84);
        write(client->fd, "230 User logged in, proceed.\r\n", 30);
        return true;
    }
    return false;
}

void pass(my_ftp_t *my_ftp, client_t *client, char **args)
{
    (void)my_ftp;
    if (client->is_logged == true) {
        write(client->fd, "530 Already logged in.\r\n", 24);
        return;
    }
    if (client->username == NULL) {
        write(client->fd, "503 Bad sequence of commands.\r\n", 31);
        return;
    }
    if (check_anonymous(my_ftp, client, args) == true)
        return;
    free(client->username);
    client->username = NULL;
    write(client->fd, "530 Login incorrect.\r\n", 22);
}
