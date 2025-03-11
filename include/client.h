/*
** EPITECH PROJECT, 2025
** client.h
** File description:
** client.h
*/

#ifndef CLIENT_H
    #define CLIENT_H

    #include <poll.h>
    #include "loop.h"

struct pollfd *create_poll(int server_fd);

#endif /* !CLIENT_H */
