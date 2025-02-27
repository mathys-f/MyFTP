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
#include "server.h"

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

static void destroy_poll(struct pollfd *fds)
{
    free(fds);
}

static void loop(int server_fd, char *path)
{
    (void)server_fd;
    (void)path;
    while (1);
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
