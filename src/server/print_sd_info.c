/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** print_sd_info
*/
#include "server.h"

void print_clients_sd(log_t *log)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (log->clients[i].sd != -1) {
            printf("Client %d: sd = %d ", i + 1, log->clients[i].sd);
            printf("Logged in: %d ", log->clients[i].logged_in);
            printf("Username: %s ", log->clients[i].usrnm);
            printf("Client UUID: %s\n", log->clients[i].uuid);
        }
    }
}
