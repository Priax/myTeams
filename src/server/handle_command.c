/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-vincent.montero-fontaine
** File description:
** handle_command
*/
#include "server.h"

const command_t COMMANDS_LIST[] = {
    {"/login", login_command},
    {"/logout", logout_cmd},
    {"/help", help_cmd},
    {"/user", cmd_user},
    {"/users", cmd_users},
    {"/send", cmd_send},
    {"/messages", cmd_messages},
    //{"/subscribe", cmd_subscribe},
    //{"/subscribed", cmd_subscribed},
    //{"/unsubscribe", cmd_unsubscribe},
    //{"/use", cmd_use},
    {"/create", cmd_create},
    //{"/list", cmd_list},
    //{"/info", cmd_info},
    {NULL, NULL}
};

int check_if_logged_in(log_t *logins, char *buffer, int i, int index)
{
    printf("Anonymous (%d): %s", logins->clients[i].sd, buffer);
    if (logins->clients[i].logged_in != 1 && index != 0 && index != 1) {
        my_putstr_fd("530 Not logged in.\r\n", logins->clients[i].sd);
        return 1;
    }
    return 0;
}

void parse_line(const char *line, char *username, char *uuid)
{
    char *token;
    char temp[strlen(line) + 1];

    strcpy(temp, line);
    token = strtok(temp, "--");
    if (token != NULL) {
        strcpy(username, token);
    } else {
        strcpy(username, "");
    }
    token = strtok(NULL, "");
    if (token != NULL && token[0] == '-') {
        strcpy(uuid, token + 1);
    } else {
        strcpy(uuid, token);
    }
}

void handle_commands(char *command, log_t *server, int i)
{
    char **args = NULL;
    int count;

    if (command == NULL || command[0] == '\0') {
        dprintf(server->clients[i].sd, "500 Unknown command\r\n");
        return;
    }
    args = tokenize(command, &count);
    add_null_terminator(&args, &count), trim_newline(args[0]);
    for (int j = 0; COMMANDS_LIST[j].name; j++) {
        if (strcmp(args[0], COMMANDS_LIST[j].name) == 0 &&
            (server->clients[i].logged_in || strcmp(args[0], "/login") == 0
            || strcmp(args[0], "/logout") == 0)) {
            COMMANDS_LIST[j].func(server, &server->clients[i], &args[1]);
            free_tokenize(args, count);
            return;
        }
    }
    free_tokenize(args, count);
    dprintf(server->clients[i].sd, "500 Unknown command or not logged in\r\n");
}
