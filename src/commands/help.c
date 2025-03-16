/*
** EPITECH PROJECT, 2025
** help.c
** File description:
** help.c
*/

#include <unistd.h>
#include <string.h>

#include "loop.h"
#include "client.h"
#include "command.h"

static const command_help_t commands_help[] = {
    {"USER", "USER <SP> <username> <CRLF> : "
        "Specify user for authentication\n", 63},
    {"PASS", "PASS <SP> <password> <CRLF> : "
        "Specify password for authentication\n", 67},
    {"QUIT", "QUIT <CRLF> : Disconnection\n", 29},
    {"HELP", "HELP [<SP> <string>] <CRLF> : List available commands\n", 55},
    {"NOOP", "NOOP <CRLF> : Do nothing\n", 28},
    {"PWD", "PWD <CRLF> : Print working directory\n", 38},
    {"CWD", "CWD <SP> <directory> <CRLF> : Change working directory\n", 56},
    {NULL, NULL, 0}
};

void help(my_ftp_t *my_ftp, client_t *client, char **args)
{
    (void)my_ftp;
    write(client->fd, "214 Help message.\n\r", 19);
    if (args[1] == NULL) {
        for (int i = 0; commands_help[i].name != NULL; i++)
            write(client->fd, commands_help[i].desc, commands_help[i].len);
        return;
    }
    for (int i = 0; commands_help[i].name != NULL; i++) {
        if (strcmp(commands_help[i].name, args[1]) == 0)
            write(client->fd, commands_help[i].desc, commands_help[i].len);
    }
}
