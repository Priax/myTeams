/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** response_messages
*/
#include "../client.h"

void response_messages(char **args)
{
    int i = 0;
    char *body;

    if (!args || !args[0] || !args[1] || !args[2] || !args[3])
        return;
    for (char **arg = &args[3]; arg[i]; i++);
    trim(args[0]), trim(args[1]), trim(args[3]);
    body = array_to_string(&args[3], i);
    client_private_message_print_messages(args[0], (time_t)args[1], body);
    free(body);
}

void response_bad_messages(char **args)
{
    if (args && args[0])
        client_error_unknown_user(args[0]);
}
