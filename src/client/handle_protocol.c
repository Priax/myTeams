/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** handle_protocol
*/
#include "client.h"

const response_t RESPONSE_LIST[] = {
    {"L01", response_login},
    {"U01", response_user},
    {"U02", response_bad_user},
    {"US01", response_users},
    {"S01", response_send},
    {"S02", response_bad_send},
    {"M01", response_messages},
    {"M02", response_bad_messages},
    {"221", response_logout},
    {"220", response_initialisation},
    {NULL, NULL}
};

void extract_uuid_and_username(const char *line, char *uuid, char *username)
{
    const char *space1 = strchr(line, ' ');
    const char *space2 = strchr(space1 + 1, ' ');

    strncpy(uuid, space1 + 1, space2 - (space1 + 1));
    uuid[space2 - (space1 + 1)] = '\0';
    strcpy(username, space2 + 1);
}

void handle_protocol(char *buffer)
{
    char **tmp = str_to_word_array(buffer);

    if (tmp == NULL || tmp[0] == NULL)
        return;
    for (int i = 0; RESPONSE_LIST[i].code != NULL; i++) {
        if (strcmp(RESPONSE_LIST[i].code, tmp[0]) == 0) {
            RESPONSE_LIST[i].func(&tmp[1]);
            free_arr(tmp);
            return;
        }
    }
    my_putstr(buffer), free_arr(tmp);
}
