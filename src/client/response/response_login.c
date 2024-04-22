/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** response_login
*/
#include "../client.h"

void response_login(char **args)
{
    trim(args[0]), remove_char(args[0], '\r'), remove_char(args[1], '\r');
    client_event_logged_in(args[0], args[1]);
}

void response_logout(char **args)
{
    if (args != NULL && args[0] != NULL && args[1] != NULL) {
        remove_char(args[0], '\r'), remove_char(args[1], '\r');
        client_event_logged_out(args[0], args[1]);
    }
}
