/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-vincent.montero-fontaine
** File description:
** quit
*/
#include "server.h"

void quit_command(log_t *logins, int i)
{
    server_event_user_logged_out(logins->clients[i].uuid_str);
    send_message_every_users(logins, "221", "Server closed\r\n");
    close(logins->clients[i].sd);
    logins->clients[i].sd = 0;
    logins->clients[i].logged_in = 0;
    if (logins->clients[i].usrnm) {
        free(logins->clients[i].usrnm);
        logins->clients[i].usrnm = NULL;
    }
    if (logins->clients[i].uuid_str) {
        free(logins->clients[i].uuid_str);
        logins->clients[i].uuid_str = NULL;
    }
}
