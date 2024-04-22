/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** str_to_word_array
*/
#include "client.h"

char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    while (src[i] != '\0' && n > i) {
        dest[i] = src[i];
        i++;
    }
    if (n > i) {
        dest[i] = '\0';
    }
    return (dest);
}

int number_words(char *str)
{
    int count = 0;
    int i;
    int tmp;

    for (i = 0; str[i] != '\0' && str[i] != '\n'; i++) {
        tmp = 0;
        while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\t')) {
            tmp = 1;
            i++;
        }
        count += tmp;
    }
    return count;
}

char **str_to_word_array(char *str)
{
    int size = number_words(str);
    int index = 0;
    int i = 0;
    char **arr = malloc(sizeof(char *) * (size + 10));

    for (i = 0; str[i] != '\0'; i++) {
        for (size = 0; str[i + size] != '\0' && str[i + size] != ' '
        && str[i + size] != '\t' && str[i + size] != '\n'; size++);
        if (size == 0)
            continue;
        arr[index] = (char *)malloc(size + 1);
        strncpy(arr[index], str + i, size);
        arr[index][size] = '\0';
        index++;
        if (str[i + size] == '\0')
            i--;
        i += size;
    }
    arr[index] = NULL;
    return arr;
}

void free_arr(char **arr)
{
    if (!arr)
        return;
    for (int i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
}
