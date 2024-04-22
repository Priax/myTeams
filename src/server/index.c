/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-vincent.montero-fontaine
** File description:
** index
*/
#include "server.h"

int get_command_index(char *buffer)
{
    char *commands[6] = {"/logout", "/login", "/send", "/users", "/user",
        NULL};
    char **given_command = str_to_word_array(buffer);

    given_command[0][strcspn(given_command[0], "\r\n")] = 0;
    for (int i = 0; commands[i]; i++) {
        if (strcmp(given_command[0], commands[i]) == 0) {
            free_arr(given_command);
            return i;
        }
    }
    free_arr(given_command);
    return -1;
}
