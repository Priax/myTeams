/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** parse_user
*/
#include "client.h"

void extract_user_info(char *token, char **username, char **uuid,
    int *logged_in_number)
{
    char *dash_position1 = strstr(token, "--");
    char *dash_position2;

    if (dash_position1 != NULL) {
        dash_position2 = strstr(dash_position1 + 2, "--");
        if (dash_position2 != NULL) {
            *username = token;
            *dash_position1 = '\0';
            *uuid = dash_position1 + 2;
            *dash_position2 = '\0';
            *logged_in_number = atoi(dash_position2 + 2);
        }
    }
}

void parse_users(char *buffer)
{
    char *token = strtok(buffer, "\n");
    char *username;
    char *uuid;
    int logged_in_number;

    while (token != NULL) {
        username = NULL;
        uuid = NULL;
        logged_in_number = 0;
        extract_user_info(token, &username, &uuid, &logged_in_number);
        if (username != NULL && uuid != NULL) {
            client_print_users(uuid, username, logged_in_number);
        }
        token = strtok(NULL, "\n");
    }
}
