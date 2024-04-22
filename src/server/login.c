/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** login
*/
#include "server.h"

void save_login_info(const char *username, const char *uuid_str)
{
    FILE *file = fopen("database/login.db", "a");

    if (file == NULL) {
        return;
    }
    fprintf(file, "%s--%s\n", username, uuid_str);
    fclose(file);
}

int read_next_line(FILE *file, char **line)
{
    size_t len = 0;
    ssize_t read;

    read = getline(line, &len, file);
    if (read == -1) {
        free(*line);
        *line = NULL;
    }
    return read;
}

int extract_uuid_from_line(const char *line, const char *username,
    char *uuid_str)
{
    char *sep = strstr(line, "--");

    if (sep == NULL)
        return 0;
    *sep = '\0';
    if (strcmp(line, username) == 0) {
        strcpy(uuid_str, sep + 2);
        return 1;
    }
    return 0;
}

int get_uuid_from_username(const char *username, char *uuid_str)
{
    FILE *file = fopen("database/login.db", "r");
    char *line = NULL;
    int read;

    if (file == NULL)
        return 0;
    read = read_next_line(file, &line);
    while (read != -1) {
        if (extract_uuid_from_line(line, username, uuid_str)) {
            fclose(file);
            free(line);
            return 1;
        }
        read = read_next_line(file, &line);
    }
    fclose(file);
    return 0;
}

//!NOM UUID LOGIN, si existe pas in save, alors fonction, sinon, 2 fonctions
void login_command(log_t *logins, client_info_t *client, char **args)
{
    char uuid_str[UUID_STR_LEN];
    char message[MAX_BODY_LENGTH];

    if (!args[0])
        return;
    trim_newline(args[0]), remove_char(args[0], '"');
    if (strlen(args[0]) == 0 || strlen(args[0]) > MAX_NAME_LENGTH)
        return;
    if (!get_uuid_from_username(args[0], uuid_str)) {
        generate_uuid(uuid_str), save_login_info(args[0], uuid_str);
        server_event_user_created(uuid_str, args[0]);
    }
    trim_newline(uuid_str), server_event_user_logged_in(uuid_str);
    uuid_parse(uuid_str, client->uuid);
    client->logged_in = 1;
    client->uuid_str = strdup(uuid_str);
    client->usrnm = strdup(args[0]);
    snprintf(message, sizeof(message), "%s %s\r\n", uuid_str, args[0]);
    send_message_every_users(logins, "L01", message);
}
