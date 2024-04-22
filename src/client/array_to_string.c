/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** array_to_string
*/
#include "client.h"

char *array_to_string(char **words, size_t num_words)
{
    size_t total_length = 0;
    char *result;
    size_t offset = 0;

    for (size_t i = 0; i < num_words; i++) {
        total_length += strlen(words[i]);
    }
    result = malloc((total_length + num_words) * sizeof(char));
    for (size_t i = 0; i < num_words; i++) {
        strcpy(result + offset, words[i]);
        offset += strlen(words[i]);
        if (i < num_words - 1) {
            result[offset] = ' ';
            offset++;
        }
    }
    result[offset] = '\0';
    return result;
}
