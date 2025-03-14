/*
** EPITECH PROJECT, 2025
** client.h
** File description:
** client.h
*/

#ifndef CLIENT_H
    #define CLIENT_H

    #include <poll.h>
    #include <stdbool.h>

    #include "loop.h"

typedef struct client_s {
    int fd;
    bool is_logged;
    char *username;
    char *password;
    char *path;
    char *buffer;
    struct client_s *next;
} client_t;

void add_client(my_ftp_t *my_ftp, int fd);
void remove_client(my_ftp_t *my_ftp, int fd);
void destroy_clients(client_t *clients);
struct pollfd *create_poll(int server_fd);
void destroy_poll(struct pollfd *fds);

#endif /* !CLIENT_H */
