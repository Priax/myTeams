/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-vincent.montero-fontaine
** File description:
** file
*/
#include "server.h"

FILE *open_file(char *file_path)
{
    FILE *file = fopen(file_path, "r");

    if (file == NULL) {
        exit(1);
    }
    return file;
}

void transfer_file(FILE *file, int data_socket, int client_sd)
{
    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    bytes_read = fread(buffer, 1, sizeof(buffer), file);
    while (bytes_read > 0) {
        if (write(data_socket, buffer, bytes_read) == -1) {
            my_putstr_fd("426 Connection closed\r\n", client_sd);
            close(data_socket);
            fclose(file), exit(84);
        }
        bytes_read = fread(buffer, 1, sizeof(buffer), file);
    }
}
