/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** cmd_user
*/
#include "server.h"

void cmd_user(log_t *serv, client_info_t *client, char **args)
{
    char *line;
    char *escaped_line;
    char username[MAX_NAME_LENGTH];
    char uuid[256];
    int logged_in;

    if (!args[0]) {
        dprintf(client->sd, "U02 (NULL)\r\n");
        return;
    }
    remove_char(args[0], '"'), trim_newline(args[0]);
    line = find_line_by_uuid("database/login.db", args[0]);
    if (!line) {
        dprintf(client->sd, "U02 %s not found\r\n", args[0]);
        return;
    }
    logged_in = serv->clients[find_client_by_uuid(serv, args[0])].logged_in;
    escaped_line = escape_special_characters(line);
    parse_line(escaped_line, username, uuid), free(escaped_line);
    dprintf(client->sd, "U01 %s %s %d\r\n", uuid, username, logged_in);
}

void user_parsing(log_t *serv, client_info_t *client,
    ssize_t *read, char *line)
{
    char username[MAX_NAME_LENGTH];
    char uuid[255];
    int i;

    if (line[*read - 1] == '\n')
        line[*read - 1] = '\0';
    if (sscanf(line, "%[^-]--%s", username, uuid) == 2) {
        i = find_client_by_uuid(serv, uuid);
        dprintf(client->sd, "US01 %s %s %d\r\n",
            uuid, username, serv->clients[i].logged_in);
    }
}

void cmd_users(log_t *serv, client_info_t *client, char **args)
{
    FILE *file = fopen("database/login.db", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    (void)args;
    if (file == NULL)
        return;
    read = getline(&line, &len, file);
    while (read != -1) {
        user_parsing(serv, client, &read, line);
        read = getline(&line, &len, file), usleep(100);
    }
    fclose(file), free(line);
}
