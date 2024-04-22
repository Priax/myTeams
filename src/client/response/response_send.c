/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** response_send
*/
#include "../client.h"

void response_send(char **args)
{
    size_t num_words = 0;
    char *body;

    if (!args[1]) {
        client_event_private_message_received(args[0], NULL);
    }
    for (char **arg = args + 1; *arg != NULL; arg++) {
        num_words++;
    }
    body = array_to_string(args + 1, num_words);
    remove_char(body, '\r');
    client_event_private_message_received(args[0], body), free(body);
}

void response_bad_send(char **args)
{
    trim(args[0]);
    client_error_unknown_user(args[0]);
}
