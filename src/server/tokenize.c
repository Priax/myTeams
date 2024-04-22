/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** tokenize
*/
#include "server.h"

void add_null_terminator(char ***args, int *count)
{
    (*args) = realloc((*args), ((*count) + 1) * sizeof(char *));
    (*args)[(*count)] = NULL;
}

char *allocate_and_copy_token(const char *buffer, int start, int length)
{
    char *token = malloc((length + 1) * sizeof(char));

    if (token == NULL) {
        exit(84);
    }
    strncpy(token, buffer + start, length);
    token[length] = '\0';
    return token;
}

void process_character(token_t *data, int i)
{
    if (data->buffer[i] == '"' && (i == 0 || data->buffer[i - 1] != '\\'))
        data->in_quotes = !data->in_quotes;
    if ((!data->in_quotes && (data->buffer[i] == ' ' || data->buffer[i] == '\t'
        || data->buffer[i] == '\n' || data->buffer[i] == '\0'))
        || data->buffer[i] == '\0') {
        if (i > data->token_start) {
            data->tokens[data->token_count] =
                allocate_and_copy_token(data->buffer, data->token_start,
                i - data->token_start);
            data->token_count++;
        }
        data->token_start = i + 1;
    }
}

char **tokenize(char *buffer, int *count)
{
    int buffer_length = strlen(buffer);
    char **tokens = malloc(buffer_length * sizeof(char *));
    token_t data = {buffer, tokens, 0, 0, 0};

    for (int i = 0; i < buffer_length; i++) {
        process_character(&data, i);
    }
    tokens = realloc(tokens, (data.token_count + 2) * sizeof(char *));
    *count = data.token_count;
    return tokens;
}

void free_tokenize(char **arr, int count)
{
    if (arr == NULL)
        return;
    for (int i = 0; i < count; i++) {
        free(arr[i]);
    }
    free(arr);
}
