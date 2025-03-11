/*
** EPITECH PROJECT, 2025
** main.c
** File description:
** main.c
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <signal.h>

#include "include/loop.h"

static my_ftp_t my_ftp = {0};

static int display_help(void)
{
    printf("USAGE: ./myftp port path\n"
        "\tport is the port number on which the server socket listens\n"
        "\tpath is the path to the home directory for the Anonymous user\n");
    return 0;
}

void handle_down_server(int sig)
{
    (void)sig;
    down_server(&my_ftp);
    exit(0);
}

static void setup_down_server(void)
{
    struct sigaction sig = {0};

    sig.sa_handler = &handle_down_server;
    sigaction(SIGINT, &sig, NULL);
    sigaction(SIGQUIT, &sig, NULL);
    sigaction(SIGTERM, &sig, NULL);
}

static int parsing(char *port, char *path)
{
    int port_nb = atoi(port);
    DIR *dir = opendir(path);

    if (port_nb <= 0 || port_nb > 65535) {
        printf("Invalid port number\n");
        return 84;
    }
    if (dir == NULL) {
        printf("Invalid path\n");
        return 84;
    }
    closedir(dir);
    setup_down_server();
    return run_server(port_nb, path, &my_ftp);
}

int main(int ac, char **av)
{
    int port;

    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return display_help();
    if (ac != 3)
        return 84;
    return parsing(av[1], av[2]);
}
