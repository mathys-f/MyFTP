/*
** EPITECH PROJECT, 2025
** main.c
** File description:
** main.c
*/

#include <string.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    int port;

    if (ac == 2 && strcmp(av[1], "-help") == 0)
        return 0;
    if (ac != 3)
        return 84;
    port = atoi(av[1]);
    if (port == 0)
        return 84;
    return 0;
}
