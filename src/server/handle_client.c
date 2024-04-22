/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-vincent.montero-fontaine
** File description:
** handle_client
*/
#include "server.h"

void handle_client_data(log_t *logins)
{
    int i;

    for (i = 0; i < MAX_CLIENTS; i++) {
        read_client(logins, i);
    }
}

char *read_input(char *buffer, log_t *l, int i)
{
    int total_read = 0;
    int valread;

    while (1) {
        valread = read(l->clients[i].sd, buffer
            + total_read, BUFFER_SIZE - total_read);
        if (valread <= 0) {
            logout_cmd(l, &l->clients[i], NULL), free(buffer);
            return NULL;
        } else {
            total_read += valread;
        }
        if (total_read >= 2 && buffer[total_read - 2] == '\r'
            && buffer[total_read - 1] == '\n') {
            break;
        }
    }
    buffer[total_read] = '\0';
    return buffer;
}

void read_client(log_t *l, int i)
{
    char *buffer;

    buffer = malloc(sizeof(char) * 1024);
    if (l->clients[i].sd > 0 && FD_ISSET(l->clients[i].sd, &l->readfds)) {
        buffer = read_input(buffer, l, i);
        if (buffer == NULL)
            return;
        handle_commands(buffer, l, i);
    }
    free(buffer);
}
