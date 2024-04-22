/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-vincent.montero-fontaine
** File description:
** read_file
*/
#include "server.h"

char *read_file(char *filepath)
{
    FILE *fs;
    size_t increase = LOWER;
    size_t allocated = increase;
    char *string = malloc(allocated);
    size_t total = 0;

    fs = fopen(filepath, "r");
    if (fs == NULL)
        return NULL;
    while (!feof(fs) && !ferror(fs)) {
        string[total] = fgetc(fs);
        total++;
        string = realloc_if_needed(string, &allocated, total, &increase);
    }
    if (ferror(fs))
        return NULL;
    string = realloc(string, total);
    string[total - 1] = '\0';
    fclose(fs);
    return string;
}

char *realloc_if_needed(char *string, size_t *allocated,
    size_t total, size_t *increase)
{
    if (total >= *allocated) {
        if (*increase >= UPPER) {
            *increase = UPPER;
        }
        *allocated += *increase;
        string = realloc(string, *allocated);
        *increase *= 2;
    }
    return string;
}
