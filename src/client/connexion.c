/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** connexion
*/
#include "client.h"

int has_all_digits(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

int get_socket(void)
{
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket == -1) {
        return (84);
    }
    return client_socket;
}

void client_connexion(char *ip, char *port, int client_socket)
{
    struct sockaddr_in server_address;

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(ip);
    if (has_all_digits(port)) {
        server_address.sin_port = htons(atoi(port));
    } else
        exit(84);
    if (connect(client_socket, (struct sockaddr *)&server_address,
        sizeof(server_address)) == -1) {
        close(client_socket), exit(84);
    }
}
