/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** trim_input
*/
#include "server.h"

void trim_newline(char *str)
{
    int len = strlen(str);

    while (len > 0 && (str[len - 1] == '\r' || str[len - 1] == '\n')) {
        --len;
        str[len] = '\0';
    }
}

void remove_surrounding_quotes(char *str)
{
    int len = strlen(str);

    if (len >= 2 && str[0] == '"' && str[len - 1] == '"') {
        memmove(str, str + 1, len - 2);
        str[len - 2] = '\0';
    }
}
