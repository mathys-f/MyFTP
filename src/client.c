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

void add_client(my_ftp_t *my_ftp, int fd)
{
    my_ftp->fds = realloc(my_ftp->fds, sizeof(struct pollfd) *
        (my_ftp->nb_fds + 1));
    if (my_ftp->fds == NULL)
        exit(84);
    my_ftp->fds[my_ftp->nb_fds].fd = fd;
    my_ftp->fds[my_ftp->nb_fds].events = POLLIN;
    my_ftp->nb_fds++;
}

struct pollfd *create_poll(int server_fd)
{
    struct pollfd *fds = malloc(sizeof(struct pollfd));

    if (fds == NULL)
        exit(84);
    fds[0].fd = server_fd;
    fds[0].events = POLLIN;
    return fds;
}

void destroy_poll(struct pollfd *fds)
{
    free(fds);
}
