/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** handle_server_input
*/
#include "client.h"

char *handle_memory(size_t *bytes_rcvd, char *buffer)
{
    char *temp_buffer;

    if (*bytes_rcvd >= BUFFER_SIZE - 1) {
        temp_buffer = realloc(buffer, BUFFER_SIZE * 2);
        if (temp_buffer == NULL) {
            free(buffer), exit(84);
        }
        buffer = temp_buffer;
    }
    return buffer;
}

char *read_server(int client_socket)
{
    char *buffer = malloc(BUFFER_SIZE);
    size_t bytes_rcvd = 0;
    ssize_t bytes_received = 0;

    bytes_received = read_c(bytes_received, client_socket, buffer, bytes_rcvd);
    while (bytes_received > 0) {
        bytes_rcvd += bytes_received;
        buffer = handle_memory(&bytes_rcvd, buffer);
        if (buffer[bytes_rcvd - 1] == '\n' && buffer[bytes_rcvd - 2] == '\r')
            break;
        bytes_received = read(client_socket, buffer + bytes_rcvd,
        BUFFER_SIZE - bytes_rcvd - 1);
    }
    if (bytes_received == -1) {
        free(buffer), close(client_socket), exit(84);
    }
    buffer[bytes_rcvd] = '\0';
    return buffer;
}

char *extract_username_from_message(char *message)
{
    char *start_quote = strchr(message, '"');
    char *end_quote;
    size_t username_len;
    char *username;

    if (start_quote == NULL)
        return NULL;
    end_quote = strchr(start_quote + 1, '"');
    if (end_quote == NULL)
        return NULL;
    username_len = end_quote - start_quote - 1;
    username = malloc(username_len + 1);
    strncpy(username, start_quote + 1, username_len);
    username[username_len] = '\0';
    return username;
}

void quit_client(int client_socket, char *message)
{
    dprintf(client_socket, "/logout\r\n");
    if (message)
        free(message);
}

void write_server(char *message, int client_socket)
{
    size_t size_buf = 0;
    ssize_t bytes_read;

    if (message != NULL) {
        free(message);
        message = NULL;
    }
    bytes_read = getline(&message, &size_buf, stdin);
    if (bytes_read == -1) {
        quit_client(client_socket, message);
        return;
    }
    if (bytes_read > 0 && message[bytes_read - 1] == '\n')
        message[bytes_read - 1] = '\0';
    write(client_socket, message, strlen(message));
    write(client_socket, "\r\n", 2), free(message);
}
