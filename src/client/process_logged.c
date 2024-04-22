/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** process_logged
*/
#include "client.h"

char *extract_uuid_from_message(const char *message)
{
    static char uuid[36 + 1];
    const char *uuid_start = strstr(message, "UUID: ");

    if (uuid_start != NULL) {
        uuid_start += strlen("UUID: ");
        strncpy(uuid, uuid_start, 36);
        uuid[36] = '\0';
        return uuid;
    }
    return NULL;
}

void extract_username(char *ptr, char *username)
{
    char *end = strchr(ptr, '-');

    if (end) {
        strncpy(username, ptr, end - ptr);
        username[end - ptr] = '\0';
    }
}

void extract_uuid(char *ptr, char *uuid)
{
    char *end = strchr(ptr, '"');

    if (end) {
        strncpy(uuid, ptr, end - ptr);
        uuid[end - ptr] = '\0';
    }
}

void process_logged_in_data(char *buffer)
{
    int logged_in = -1;
    char username[256];
    char uuid[256];
    char *ptr;

    ptr = strstr(buffer, "{\"logged_in\": ");
    ptr += strlen("{\"logged_in\": ");
    sscanf(ptr, "%d", &logged_in);
    ptr = strstr(ptr, "\"line\": \"");
    if (ptr) {
        ptr += strlen("\"line\": \"");
        extract_username(ptr, username);
    }
    ptr = strstr(ptr, "--");
    if (ptr) {
        ptr += strlen("--");
        extract_uuid(ptr, uuid);
    }
    client_print_user(uuid, username, logged_in);
}
