/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** uuid
*/
#include "server.h"

char *read_line(FILE *file)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read = getline(&line, &len, file);

    if (read != -1) {
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';
        return line;
    } else {
        free(line);
        return NULL;
    }
}

char *extract_uuid(char *line)
{
    char *separator_pos = strstr(line, "--");

    if (separator_pos != NULL) {
        return separator_pos + 2;
    }
    return NULL;
}

char *find_line_by_uuid(char *filename, char *uuid)
{
    FILE *file = fopen(filename, "r");
    char *line;
    char *line_uuid;

    if (file == NULL)
        return NULL;
    line = read_line(file);
    while (line != NULL) {
        line_uuid = extract_uuid(line);
        if (line_uuid != NULL && strcmp(line_uuid, uuid) == 0) {
            fclose(file);
            return line;
        }
        free(line);
        line = read_line(file);
    }
    fclose(file);
    return NULL;
}

char *escape_special_characters(const char *input)
{
    int len = strlen(input);
    char *output = malloc(2 * len + 1);
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (input[i] == '"' || input[i] == '\\') {
            output[j] = '\\';
            j++;
        }
        output[j] = input[i];
        j++;
    }
    output[j] = '\0';
    return output;
}

void generate_uuid(char *uuid_str)
{
    uuid_t new_client_uuid;

    uuid_generate(new_client_uuid);
    uuid_unparse(new_client_uuid, uuid_str);
    trim_newline(uuid_str);
}
