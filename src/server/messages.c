/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** messages
*/
#include "server.h"

void store_message(const char *sender_uuid, const char *receiver_uuid,
    const char *message, time_t timestamp)
{
    FILE *file;
    char filename[FILENAME_MAX];

    snprintf(filename, FILENAME_MAX,
        "database/%s_%s.txt", sender_uuid, receiver_uuid);
    file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "%ld %s: %s\n", timestamp, sender_uuid, message);
        fclose(file);
    }
}

void retrieve_messages(const char *sender_uuid,
    const char *receiver_uuid, client_info_t *client)
{
    FILE *file;
    char filename[FILENAME_MAX];
    char message[1024];
    time_t timestamp;

    snprintf(filename, FILENAME_MAX,
        "database/%s_%s.txt", sender_uuid, receiver_uuid);
    file = fopen(filename, "r");
    if (file != NULL) {
        while (fscanf(file, "%ld %[^\n]", &timestamp, message) == 2) {
            dprintf(client->sd, "M01 %s %ld %s\r\n", sender_uuid,
                (long)timestamp, message), usleep(100);
        }
        fclose(file);
    }
}
