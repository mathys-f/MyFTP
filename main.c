/*
** EPITECH PROJECT, 2025
** main.c
** File description:
** main.c
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "include/loop.h"

static int display_help(void)
{
    printf("USAGE: ./myftp port path\n"
        "\tport is the port number on which the server socket listens\n"
        "\tpath is the path to the home directory for the Anonymous user\n");
    return 0;
}

int main(int ac, char **av)
{
    int port;

    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return display_help();
    if (ac != 3)
        return 84;
    port = atoi(av[1]);
    if (port == 0)
        return 84;
    return run_server(port, av[2]);
}
