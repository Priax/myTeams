/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-vincent.montero-fontaine
** File description:
** server
*/
#include "server.h"

int create_socket(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stdout, "Usage: %s <server_port>\n", argv[0]);
        return -1;
    }
    if (strcmp(argv[1], "-help") == 0) {
        printf("USAGE: %s port\n\tport is the port number", argv[0]);
        printf("on which the server socket listens.\n");
        exit(0);
    }
    return socket(PF_INET, SOCK_STREAM, 0);
}

void add_client_socket(int clientSocket, log_t *logins,
    struct sockaddr_in *clientSa)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (logins->clients[i].sd == 0) {
            logins->clients[i].sd = clientSocket;
            logins->clients[i].logged_in = 0;
            logins->clients[i].usrnm = NULL;
            break;
        }
    }
    if (clientSocket > logins->max_sd)
        logins->max_sd = clientSocket;
    printf("New connection, fd: %d, ip: %s, port: %d\n",
            clientSocket, inet_ntoa(clientSa->sin_addr),
            ntohs(clientSa->sin_port));
}

int main(int argc, char **argv)
{
    int rc;
    int on = 1;
    int s = create_socket(argc, argv);

    if (s < 0)
        return 84;
    rc = setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);
    if (rc < 0)
        return 84;
    rc = bind_socket(s, argv);
    if (rc < 0)
        return 84;
    rc = start_listening(s);
    if (rc < 0)
        return 84;
    handle_connections(s);
    close(s);
    return 0;
}
