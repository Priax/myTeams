/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** help
*/
#include "server.h"

void help_cmd(log_t *logins, client_info_t *client, char **args)
{
    (void)logins;
    (void)client;
    (void)args;
    dprintf(client->sd, "HELP\r\n");
}
