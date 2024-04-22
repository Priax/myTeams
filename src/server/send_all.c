/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** send_all
*/
#include "server.h"

void send_message_every_users(log_t *server, char *code, char *args)
{
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (!uuid_is_null(server->clients[i].uuid)) {
            dprintf(server->clients[i].sd, "%s %s", code, args);
        }
    }
}
