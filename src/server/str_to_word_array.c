/*
** EPITECH PROJECT, 2023
** Tek1
** File description:
** Tek1
*/
#include "server.h"

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
    int i;
    char **arr = malloc(sizeof(char *) * (size + 2));

    for (i = 0; str[i] != '\0'; i++) {
        for (size = 0; str[i + size] != '\0' && str[i + size] != ' '
        && str[i + size] != '\t' && str[i + size] != '\n'; size++);
        if (size == 0)
            continue;
        arr[index] = (char *)malloc(size + 1);
        my_strncpy(arr[index], str + i, size);
        arr[index][size] = '\0';
        index++;
        if (str[i + size] == '\0')
            i--;
        i += size;
    }
    arr[index] = NULL;
    return arr;
}

int number_words_delim(char *str, char delimiter)
{
    int count = 0;
    int i;
    int tmp;

    for (i = 0; str[i] != '\0' && str[i] != '\n'; i++) {
        tmp = 0;
        while (str[i] != '\0' && (str[i] == ' '
            || str[i] == '\t' || str[i] == delimiter)) {
            tmp = 1;
            i++;
        }
        count += tmp;
    }
    return count;
}

char **str_to_word_array_delim(char *str, char delimiter)
{
    int s = number_words_delim(str, delimiter);
    int index = 0;
    int i;
    char **arr = malloc(sizeof(char *) * (s + 2));

    for (i = 0; str[i] != '\0'; i++) {
        for (s = 0; str[i + s] != '\0' && str[i + s] != delimiter && str[i + s]
            != ' ' && str[i + s] != '\t' && str[i + s] != '\n'; s++);
        if (s == 0)
            continue;
        arr[index] = (char *)malloc(s + 1);
        my_strncpy(arr[index], str + i, s);
        arr[index][s] = '\0';
        index++;
        if (str[i + s] == '\0')
            i--;
        i += s;
    }
    arr[index] = NULL;
    return arr;
}
