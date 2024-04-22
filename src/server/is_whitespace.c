/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** is_whitespace
*/
#include "server.h"

int is_whitespace(char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}
