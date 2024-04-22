/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** set_socket
*/
#include "server.h"

fd_set set_client_socket(log_t *logins, int i)
{
    if (logins->clients[i].sd > 0) {
        FD_SET(logins->clients[i].sd, &logins->readfds);
    }
    return logins->readfds;
}
