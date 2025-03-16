/*
** EPITECH PROJECT, 2025
** pasv.c
** File description:
** pasv.c
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "loop.h"
#include "server.h"
#include "client.h"

static int get_port(int data_fd)
{
    struct sockaddr_in data_addr;
    socklen_t len = sizeof(data_addr);

    if (getsockname(data_fd, (struct sockaddr *)&data_addr, &len) == -1)
        exit(84);
    return ntohs(data_addr.sin_port);
}

void pasv(my_ftp_t *my_ftp, client_t *client, char **args)
{
    int port = 0;

    (void)my_ftp;
    (void)args;
    if (client->is_logged == false) {
        write(client->fd, "530 Not logged in.\r\n", 20);
        return;
    }
    if (client->data_fd != -1)
        close(client->data_fd);
    client->data_fd = create_server(0);
    port = get_port(client->data_fd);
    dprintf(client->fd, "227 Entering Passive Mode (127,0,0,1,%d,%d).\r\n",
        port / 256, port % 256);
}
