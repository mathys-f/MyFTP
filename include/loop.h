/*
** EPITECH PROJECT, 2025
** loop.h
** File description:
** loop.h
*/

#ifndef LOOP_H
    #define LOOP_H

typedef struct client_s client_t;

typedef struct my_ftp_s {
    int port;
    char *path;
    int server_fd;
    struct pollfd *fds;
    int nb_fds;
    client_t **clients;
} my_ftp_t;

int run_server(int port, char *path, my_ftp_t *my_ftp);
void down_server(my_ftp_t *my_ftp);

#endif /* !LOOP_H */
