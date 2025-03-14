/*
** EPITECH PROJECT, 2025
** user.c
** File description:
** user.c
*/

#include <unistd.h>
#include <string.h>

#include "loop.h"
#include "client.h"

void user(my_ftp_t *my_ftp, client_t *client, char **args)
{
    (void)my_ftp;
    if (client->is_logged == true) {
        write(client->fd, "530 Already logged in.\r\n", 24);
        return;
    }
    if (args[1] == NULL) {
        write(client->fd, "501 Syntax error in parameters or arguments.\r\n",
            46);
        return;
    }
    client->username = strdup(args[1]);
    write(client->fd, "331 User name okay, need password.\r\n", 36);
}
