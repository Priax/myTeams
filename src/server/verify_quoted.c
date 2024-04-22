/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** verify_quoted
*/
#include "server.h"

int verify_quoted_args(char *buffer)
{
    int count;
    char **arr = tokenize(buffer, &count);
    int length;
    int search;

    if (count <= 1)
        return 1;
    for (int i = 1; i < count; i++) {
        length = strlen(arr[i]);
        search = (i == count - 1) ? 2 : 1;
        if (length <= 2 || arr[i][0] != '"'
            || arr[i][length - search] != '"') {
            free_tokenize(arr, count);
            return 0;
        }
    }
    free_tokenize(arr, count);
    return 1;
}
