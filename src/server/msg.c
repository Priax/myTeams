/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** msg
*/
#include "server.h"

int find_client_by_uuid(log_t *logins, char *uuid_str)
{
    int i;
    uuid_t target_uuid;

    uuid_clear(target_uuid);
    if (uuid_parse(uuid_str, target_uuid) != 0) {
        printf("Error: Failed to parse UUID string: %s\n", uuid_str);
        return -1;
    }
    for (i = 0; i < MAX_CLIENTS; i++) {
        if (uuid_compare(logins->clients[i].uuid, target_uuid) == 0) {
            return i;
        }
    }
    return -1;
}

void remove_char(char *str, char c)
{
    char *src = str;
    char *dst = str;

    while (*src) {
        if (*src != c) {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
}

void msg_command(log_t *log, char *buffer, int i)
{
    int count;
    int rcver;
    char **arr = tokenize(buffer, &count);

    if (count != 3)
        return;
    for (int i = 1; i < count; i++)
        remove_char(arr[i], '"');
    rcver = find_client_by_uuid(log, arr[1]);
    if (rcver == -1) {
        my_putstr_fd("Recipient not found.\r\n", log->clients[i].sd);
        return;
    }
    dprintf(log->clients[rcver].sd, "400 %s %s\r\n",
        log->clients[i].uuid_str, arr[2]), remove_char(arr[2], '\r');
    server_event_private_message_sended(log->clients[i].uuid_str,
        log->clients[rcver].uuid_str, arr[2]);
    add_message(log->clients[rcver].uuid_str, arr[2], log->db);
    my_putstr_fd("Sent.\r\n", log->clients[i].sd), free_tokenize(arr, count);
}

void cmd_send(log_t *logins, client_info_t *client, char **args)
{
    char *uuid = delete_quotes(args[0]);
    size_t num_words = 0;
    char *body;
    int i;
    time_t message_timestamp = time(NULL);

    for (char **arg = args + 1; *arg != NULL; arg++)
        num_words++;
    body = delete_quotes(array_to_string(args + 1, num_words));
    i = find_client_by_uuid(logins, uuid);
    remove_char(body, '\r'), remove_char(body, '"');
    if (i == -1) {
        dprintf(client->sd, "S02 %s %s\r\n", uuid, body);
        return;
    }
    server_event_private_message_sended(client->uuid_str, uuid, body);
    dprintf(logins->clients[i].sd, "S01 %s %s\r\n", uuid, body);
    store_message(client->uuid_str, uuid, body, message_timestamp);
}

void cmd_messages(log_t *logins, client_info_t *client, char **args)
{
    char *uuid_str;
    uuid_t uuid;

    if (!args || !args[0])
        return;
    (void)logins;
    uuid_str = delete_quotes(args[0]);
    remove_char(uuid_str, '"'), trim_newline(uuid_str);
    if (uuid_parse(uuid_str, uuid) != 0) {
        dprintf(client->sd, "M02 %s\r\n", uuid_str);
        return;
    }
    retrieve_messages(client->uuid_str, uuid_str, client);
    retrieve_messages(uuid_str, client->uuid_str, client);
}
