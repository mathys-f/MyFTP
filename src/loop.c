/*
** EPITECH PROJECT, 2025
** loop.c
** File description:
** loop.c
*/

#include <poll.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

#include "client.h"
#include "loop.h"
#include "server.h"
#include "command.h"

static void check_for_new_client(my_ftp_t *my_ftp)
{
    int new_fd = 0;

    if (my_ftp->fds[0].revents & POLLIN) {
        new_fd = accept(my_ftp->fds[0].fd, NULL, NULL);
        if (new_fd == -1)
            exit(84);
        add_client(my_ftp, new_fd);
        my_ftp->nb_fds++;
        write(new_fd, "220 Service ready for new user.\r\n", 33);
    }
}

static void check_for_client_command(my_ftp_t *my_ftp)
{
    for (int i = 1; i < my_ftp->nb_fds; i++) {
        if (my_ftp->fds[i].revents & POLLIN)
            handle_client_command(my_ftp, my_ftp->fds[i].fd);
    }
}

static void loop(my_ftp_t *my_ftp)
{
    int ready = 0;

    while (1) {
        ready = poll(my_ftp->fds, my_ftp->nb_fds, -1);
        if (ready == -1)
            exit(84);
        check_for_new_client(my_ftp);
        check_for_client_command(my_ftp);
    }
}

int run_server(int port, char *path, my_ftp_t *my_ftp)
{
    my_ftp->port = port;
    my_ftp->path = path;
    my_ftp->server_fd = create_server(port);
    my_ftp->fds = create_poll(my_ftp->server_fd);
    my_ftp->nb_fds = 1;
    my_ftp->clients = NULL;
    loop(my_ftp);
    down_server(my_ftp);
    return 0;
}

void down_server(my_ftp_t *my_ftp)
{
    destroy_poll(my_ftp->fds);
    destroy_server(my_ftp->server_fd);
    destroy_clients(my_ftp->clients);
}
