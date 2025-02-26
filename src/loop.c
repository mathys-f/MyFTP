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

static struct pollfd *create_poll(int server_fd)
{
    struct pollfd *fds = malloc(sizeof(struct pollfd) * 11);

    if (fds == NULL)
        exit(84);
    fds[0].fd = server_fd;
    fds[0].events = POLLIN;
    for (int i = 1; i < 11; i++) {
        fds[i].fd = -1;
        fds[i].events = POLLIN;
    }
    return fds;
}

int run_server(int port, char *path)
{
    int server_fd = create_server(port);
    struct pollfd *fds = create_poll(server_fd);

    loop(server_fd, path);
    destroy_poll(fds);
    destroy_server(server_fd);
    return 0;
}
