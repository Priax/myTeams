/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-vincent.montero-fontaine
** File description:
** accept_connect
*/
#include "server.h"

int accept_connec(int data_socket, int client_sd)
{
    int ready;
    int accepted_socket;
    fd_set readfds;

    FD_ZERO(&readfds);
    FD_SET(data_socket, &readfds);
    ready = select(data_socket + 1, &readfds, NULL, NULL, NULL);
    if (ready < 0) {
        exit(84);
    }
    accepted_socket = accept(data_socket, NULL, NULL);
    if (accepted_socket < 0) {
        my_putstr_fd("425 Can't open data connection\r\n", client_sd);
        exit(84);
    }
    return accepted_socket;
}

int connect_connec(int data_socket, struct sockaddr_in* client_addr)
{
    int result;

    result = connect(data_socket, (struct sockaddr*)client_addr,
        sizeof(*client_addr));
    if (result < 0) {
        return -1;
    }
    return data_socket;
}
