/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** response_user
*/
#include "../client.h"

void response_user(char **args)
{
    trim(args[0]), trim(args[1]), trim(args[2]);
    client_print_user(args[0], args[1], atoi(args[2]));
}

void response_bad_user(char **args)
{
    if (args[0]) {
        trim(args[0]);
        client_error_unknown_user(args[0]);
    }
}

void response_users(char **args)
{
    trim(args[0]), trim(args[1]), trim(args[2]);
    client_print_users(args[0], args[1], atoi(args[2]));
}
