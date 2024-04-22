/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** logout
*/
#include "server.h"

void logout_cmd(log_t *logins, client_info_t *cli, char **args)
{
    char *response;

    (void)args;
    if (cli->uuid_str) {
        response = malloc(strlen(cli->uuid_str) + strlen(cli->usrnm) + 4);
        sprintf(response, "%s %s\r\n", cli->uuid_str, cli->usrnm);
        send_message_every_users(logins, "221", response), free(response);
        server_event_user_logged_out(cli->uuid_str);
    }
    if (cli->usrnm) {
        free(cli->usrnm);
        cli->usrnm = NULL;
    }
    if (cli->uuid_str) {
        free(cli->uuid_str);
        cli->uuid_str = NULL;
    }
    close(cli->sd);
    cli->sd = 0;
    cli->logged_in = 0;
}
