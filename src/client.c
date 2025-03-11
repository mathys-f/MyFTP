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

static void add_client_data(my_ftp_t *my_ftp, int fd)
{
    client_t *client = malloc(sizeof(client_t));

    if (client == NULL)
        exit(84);
    client->fd = fd;
    client->is_logged = false;
    client->username = NULL;
    client->password = NULL;
    client->path = NULL;
    client->next = my_ftp->clients;
    my_ftp->clients = client;
}

void add_client(my_ftp_t *my_ftp, int fd)
{
    my_ftp->fds = realloc(my_ftp->fds, sizeof(struct pollfd) *
        (my_ftp->nb_fds + 1));
    if (my_ftp->fds == NULL)
        exit(84);
    my_ftp->fds[my_ftp->nb_fds].fd = fd;
    my_ftp->fds[my_ftp->nb_fds].events = POLLIN;
    my_ftp->fds[my_ftp->nb_fds].revents = 0;
    add_client_data(my_ftp, fd);
}

static void remove_client_data(client_t **client, int fd)
{
    client_t *prev = NULL;
    client_t *current = *client;

    while (current != NULL && current->fd != fd) {
        prev = current;
        current = current->next;
    }
    if (current == NULL)
        return;
    if (prev == NULL)
        *client = current->next;
    else
        prev->next = current->next;
    free(current->username);
    free(current->password);
    free(current->path);
    free(current);
}

void remove_client(my_ftp_t *my_ftp, int fd)
{
    int index = 0;

    while (index < my_ftp->nb_fds && my_ftp->fds[index].fd != fd)
        index++;
    if (index == my_ftp->nb_fds)
        return;
    for (int i = index; i < my_ftp->nb_fds - 1; i++)
        my_ftp->fds[i] = my_ftp->fds[i + 1];
    my_ftp->fds = realloc(my_ftp->fds, sizeof(struct pollfd) *
        (my_ftp->nb_fds - 1));
    if (my_ftp->fds == NULL)
        exit(84);
    my_ftp->nb_fds--;
    remove_client_data(&my_ftp->clients, fd);
    close(fd);
}

void destroy_clients(client_t *clients)
{
    client_t *current = clients;
    client_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        close(current->fd);
        free(current->username);
        free(current->password);
        free(current->path);
        free(current);
        current = next;
    }
}

struct pollfd *create_poll(int server_fd)
{
    struct pollfd *fds = malloc(sizeof(struct pollfd));

    if (fds == NULL)
        exit(84);
    fds[0].fd = server_fd;
    fds[0].events = POLLIN;
    fds[0].revents = 0;
    return fds;
}

void destroy_poll(struct pollfd *fds)
{
    free(fds);
}
