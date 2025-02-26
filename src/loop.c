/*
** EPITECH PROJECT, 2025
** loop.c
** File description:
** loop.c
*/

#include <poll.h>
#include <stddef.h>
#include <stdlib.h>

#include "loop.h"

int run_server(int port, char *path)
{
    int server_fd = create_server(port);
    struct pollfd *fds = create_poll(server_fd);

    loop(server_fd, path);
    destroy_poll(fds);
    destroy_server(server_fd);
    return 0;
}
