/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** handle_client
*/
#include "client.h"

//! Faire une fonction qui selon le code, renvoie vers la bonne fonction
void handle_client_socket(int client_socket)
{
    char *buffer = read_server(client_socket);

    handle_protocol(buffer);
    if (buffer)
        free(buffer);
}
