/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** process_login
*/
#include "server.h"

void process_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    char line[256];
    char username[256];
    char uuid[256];

    if (file == NULL)
        return;
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        if (sscanf(line, "%[^-]--%s", username, uuid) == 2) {
            server_event_user_loaded(uuid, username);
        }
    }
    fclose(file);
}
