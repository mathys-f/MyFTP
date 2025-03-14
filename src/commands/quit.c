/*
** EPITECH PROJECT, 2025
** quit.c
** File description:
** quit.c
*/

#include <unistd.h>

#include "loop.h"
#include "client.h"

void quit(my_ftp_t *my_ftp, client_t *client, char **args)
{
    (void)args;
    write(client->fd, "221 Service closing control connection.\r\n", 41);
    remove_client(my_ftp, client->fd);
}
