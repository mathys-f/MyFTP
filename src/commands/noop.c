/*
** EPITECH PROJECT, 2025
** noop.c
** File description:
** noop.c
*/

#include <unistd.h>

#include "loop.h"
#include "client.h"

void noop(my_ftp_t *my_ftp, client_t *client, char **args)
{
    (void)my_ftp;
    (void)args;
    write(client->fd, "200 Command okay.\r\n", 20);
}
