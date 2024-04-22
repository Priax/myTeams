/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** is_white
*/
#include "client.h"

int is_whitespace(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

void trim(char *str)
{
    int start = 0;
    int end = strlen(str) - 1;

    while (isspace(str[start]) || str[start] == '\r')
        start++;
    while ((end >= start) && (isspace(str[end]) || str[end] == '\r'))
        end--;
    memmove(str, str + start, end - start + 1);
    str[end - start + 1] = '\0';
}
