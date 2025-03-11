/*
** EPITECH PROJECT, 2025
** client.c
** File description:
** client.c
*/

#include <poll.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#include "client.h"

void add_client(my_ftp_t *my_ftp, int fd)
{
    my_ftp->fds = realloc(my_ftp->fds, sizeof(struct pollfd) *
        (my_ftp->nb_fds + 1));
    if (my_ftp->fds == NULL)
        exit(84);
    my_ftp->fds[my_ftp->nb_fds].fd = fd;
    my_ftp->fds[my_ftp->nb_fds].events = POLLIN;
    my_ftp->clients = realloc(my_ftp->clients, sizeof(client_t *) *
        (my_ftp->nb_fds));
    if (my_ftp->clients == NULL)
        exit(84);
    my_ftp->clients[my_ftp->nb_fds - 1] = malloc(sizeof(client_t));
    if (my_ftp->clients[my_ftp->nb_fds - 1] == NULL)
        exit(84);
    my_ftp->clients[my_ftp->nb_fds - 1]->fd = fd;
    my_ftp->clients[my_ftp->nb_fds - 1]->is_logged = false;
    my_ftp->clients[my_ftp->nb_fds - 1]->username = NULL;
    my_ftp->clients[my_ftp->nb_fds - 1]->password = NULL;
    my_ftp->clients[my_ftp->nb_fds - 1]->path = NULL;
}

void remove_client(my_ftp_t *my_ftp, int index)
{
    close(my_ftp->clients[index]->fd);
    free(my_ftp->clients[index]);
    for (int i = index; i < my_ftp->nb_fds - 1; i++) {
        my_ftp->clients[i] = my_ftp->clients[i + 1];
        my_ftp->fds[i + 1] = my_ftp->fds[i + 2];
    }
    my_ftp->nb_fds--;
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
