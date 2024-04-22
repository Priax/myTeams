/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** read_c
*/
#include "client.h"

ssize_t read_c(ssize_t bytes_received, int client_socket,
    char *buffer, size_t bytes_rcvd)
{
    bytes_received = read(client_socket, buffer + bytes_rcvd,
        BUFFER_SIZE - bytes_rcvd - 1);
    if (bytes_received == 0) {
        free(buffer), close(client_socket), exit(0);
    }
    return bytes_received;
}
