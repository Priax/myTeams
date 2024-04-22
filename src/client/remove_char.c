/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** remove_char
*/
#include "client.h"

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
