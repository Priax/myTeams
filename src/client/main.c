/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** main
*/
#include "client.h"

int my_strlen(char const *str)
{
    int i = 0;

    if (!str)
        return i;
    while (str[i])
        i++;
    return i;
}

void my_putstr(char const *str)
{
    write(1, str, my_strlen(str));
}

void handle_client(fd_set read_fds, char *message, int client_socket)
{
    if (FD_ISSET(client_socket, &read_fds))
        handle_client_socket(client_socket);
    if (FD_ISSET(0, &read_fds))
        write_server(message, client_socket);
}

int main(int argc, char **argv)
{
    int client_socket;
    char *message = NULL;
    fd_set read_fds;

    if (argc != 3) {
        fprintf(stdout, "Usage: %s <server_ip> <port>\n", argv[0]), exit(84);
    }
    client_socket = get_socket();
    client_connexion(argv[1], argv[2], client_socket);
    while (1) {
        if (setup_select(&read_fds, client_socket) == -1)
            exit(84);
        handle_client(read_fds, message, client_socket);
    }
    close(client_socket);
    return 0;
}
