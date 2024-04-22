/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** select
*/
#include "client.h"

int setup_select(fd_set *read_fds, int client_socket)
{
    int max_fd;

    FD_ZERO(read_fds);
    FD_SET(STDIN_FILENO, read_fds);
    FD_SET(client_socket, read_fds);
    max_fd = (STDIN_FILENO > client_socket) ? STDIN_FILENO : client_socket;
    if (select(FD_SETSIZE, read_fds, NULL, NULL, NULL) <= 0)
        exit(0);
    return max_fd + 1;
}
