/*
** EPITECH PROJECT, 2025
** client.c
** File description:
** client.c
*/

#include <poll.h>
#include <stddef.h>
#include <stdlib.h>

#include "client.h"
#include "loop.h"

struct pollfd *create_poll(int server_fd)
{
    struct pollfd *fds = malloc(sizeof(struct pollfd));

    if (fds == NULL)
        exit(84);
    fds[0].fd = server_fd;
    fds[0].events = POLLIN;
    return fds;
}
