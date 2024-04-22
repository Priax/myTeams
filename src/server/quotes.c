/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** quotes
*/
#include "server.h"

char *delete_quotes(char *str)
{
    char *new_str = NULL;
    size_t size = strlen(str);

    if (str == NULL)
        return (NULL);
    if (str[0] == '"' && str[size - 1] == '"') {
        new_str = malloc(sizeof(char) * (size - 1));
        if (new_str == NULL)
            return (NULL);
        for (size_t i = 0; i < size - 2; i++)
            new_str[i] = str[i + 1];
        new_str[size - 2] = '\0';
        return (new_str);
    }
    return (str);
}
