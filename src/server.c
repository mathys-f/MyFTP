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

static void init_queue(int server_fd)
{
    if (listen(server_fd, 10) == -1)
        exit(84);
}

static void config_socket(int server_fd, int port)
{
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_fd, (struct sockaddr *)&server_addr,
        sizeof(server_addr)) == -1)
        exit(84);
}

static int create_socket(void)
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1)
        exit(84);
    return server_fd;
}

int create_server(int port)
{
    int server_fd = create_socket();

    config_socket(server_fd, port);
    init_queue(server_fd);
    return server_fd;
}

void destroy_server(int server_fd)
{
    if (close(server_fd) == -1)
        exit(84);
}
