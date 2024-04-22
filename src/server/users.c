/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** users
*/
#include "server.h"

void user_command(log_t *logins, char *buffer, int client_socket)
{
    int count;
    char **arr = tokenize(buffer, &count), *escaped_line, *line;
    char response[512];
    int socket;
    int logged_in;

    remove_char(arr[1], '"'), trim_newline(arr[1]);
    line = find_line_by_uuid("database/login.db", arr[1]);
    if (!line) {
        dprintf(client_socket, "User with UUID %s not found.\r\n", arr[1]);
        free_tokenize(arr, count);
        return;
    }
    socket = find_client_by_uuid(logins, arr[1]);
    logged_in = logins->clients[socket].logged_in;
    escaped_line = escape_special_characters(line);
    snprintf(response, sizeof(response),
        "{\"logged_in\": %d, \"line\": \"%s\"}", logged_in, escaped_line);
    dprintf(client_socket, "%s\r\n", response);
    free(escaped_line), free_tokenize(arr, count), free(line);
}

void users_command(log_t *logins, const char *filename, int client_socket)
{
    FILE *file = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char uuid[37];
    int i;

    if (file == NULL)
        return;
    read = getline(&line, &len, file);
    while (read != -1) {
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';
        sscanf(line, "%*[^-]--%s", uuid);
        i = find_client_by_uuid(logins, uuid);
        dprintf(logins->clients[client_socket].sd, "300\n%s--%d\r\n",
            line, logins->clients[i].logged_in);
        read = getline(&line, &len, file);
    }
    free(line), fclose(file);
}
