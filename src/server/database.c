/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** database
*/
#include "server.h"

void initialize_database(database_t *db)
{
    TAILQ_INIT(&db->messages);
}

void add_message(const char *sender, const char *body, database_t *db)
{
    message_t *msg = (message_t *)malloc(sizeof(message_t));

    if (msg == NULL) {
        return;
    }
    strncpy(msg->sender, sender, MAX_NAME_LENGTH);
    strncpy(msg->body, body, MAX_BODY_LENGTH);
    TAILQ_INSERT_TAIL(&db->messages, msg, entries);
}

void save_to_db(const char *filename, database_t *db)
{
    FILE *file = fopen(filename, "ab");
    message_t *msg;

    if (file == NULL) {
        return;
    }
    TAILQ_FOREACH(msg, &db->messages, entries) {
        fwrite(msg, sizeof(message_t), 1, file);
    }
    fclose(file);
}

void print_db_contents(const char *filename, database_t *db)
{
    FILE *file = fopen(filename, "rb");
    message_t *msg;
    message_t *temp_msg;

    if (file == NULL) {
        return;
    }
    TAILQ_FOREACH(msg, &db->messages, entries) {
        printf("Sender: %s\n", msg->sender);
        printf("Body: %s\n", msg->body), printf("\n");
    }
    while (!TAILQ_EMPTY(&db->messages)) {
        temp_msg = TAILQ_FIRST(&db->messages);
        TAILQ_REMOVE(&db->messages, temp_msg, entries);
        free(temp_msg);
    }
    fclose(file);
}

void load_from_db(const char *filename, database_t *db)
{
    FILE *file = fopen(filename, "rb");
    message_t msg;
    message_t *new_msg;

    if (file == NULL) {
        return;
    }
    TAILQ_INIT(&db->messages);
    while (fread(&msg, sizeof(message_t), 1, file) == 1) {
        new_msg = (message_t *)malloc(sizeof(message_t));
        if (new_msg == NULL) {
            fclose(file);
            return;
        }
        memcpy(new_msg, &msg, sizeof(message_t));
        TAILQ_INSERT_TAIL(&db->messages, new_msg, entries);
    }
    fclose(file);
}
