/*
** EPITECH PROJECT, 2025
** port.c
** File description:
** port.c
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "loop.h"
#include "server.h"
#include "client.h"

void port(my_ftp_t *my_ftp, client_t *client, char **args)
{
    int port = 0;

    (void)my_ftp;
    if (client->is_logged == false) {
        write(client->fd, "530 Not logged in.\r\n", 20);
        return;
    }
    if (client->data_fd != -1)
        close(client->data_fd);
    port = atoi(args[1]);
    if (port <= 0 || port > 65535) {
        write(client->fd, "500 Invalid port.\r\n", 20);
        return;
    }
    client->data_fd = create_server(port);
    write(client->fd, "200 command okay.\r\n", 19);
}
