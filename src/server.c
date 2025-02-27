/*
** EPITECH PROJECT, 2025
** server.c
** File description:
** server.c
*/

#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "server.h"

int create_server(int port)
{
    int server_fd = create_socket();

    config_socket(server_fd, port);
    init_queue(server_fd);
    return server_fd;
}
