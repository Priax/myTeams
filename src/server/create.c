/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** create
*/
#include "server.h"

void cmd_create(log_t *logins, client_info_t *client, char **args)
{
    (void)logins;
    (void)client;
    my_show_word_array(args, "\n");
    return;
}
