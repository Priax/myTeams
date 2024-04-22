/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-vincent.montero-fontaine
** File description:
** arr_func
*/
#include "server.h"

void free_arr(char **arr)
{
    int i;

    for (i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
}

void my_show_word_array(char **arr, char *delim)
{
    int i;

    for (i = 0; arr[i]; i++) {
        my_putstr(arr[i]);
        if (arr[i + 1])
            my_putstr(delim);
    }
    my_putstr("\n");
}

int my_lenarr(char **arr)
{
    int a = 0;

    if (!arr)
        return a;
    while (arr[a] != NULL)
        a++;
    return (a);
}
