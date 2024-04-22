/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_
    #include <stdio.h>
    #include <stdlib.h>
    #include <dlfcn.h>
    #include <unistd.h>
    #include <string.h>
    #include <arpa/inet.h>
    #include <ctype.h>
    #include <errno.h>
    #include <sys/select.h>
    #include "../../libs/myteams/logging_client.h"
    #define BUFFER_SIZE 1024
    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512

typedef struct {
    char *buffer;
    char **tokens;
    int token_count;
    int token_start;
    int in_quotes;
} token_t;

typedef struct response_s {
    const char *code;
    void (*func)(char **args);
} response_t;

extern const response_t RESPONSE_LIST[];

/* main */
int my_strlen(char const *str);
void my_putstr(char const *str);

/* connexion */
int has_all_digits(char *str);
int get_socket(void);
void client_connexion(char *ip, char *port, int client_socket);

/* handle_server_input */
char *handle_memory(size_t *total_bytes_received, char *buffer);
char *read_server(int client_socket);
void write_server(char *message, int client_socket);

/* handle_client */
void handle_client_socket(int client_socket);

/* select */
int setup_select(fd_set *read_fds, int client_socket);

/* is_white */
int is_whitespace(char c);
void trim(char *str);

/* process_logged */
char *extract_uuid_from_message(const char *message);
void extract_username(char *ptr, char *username);
void extract_uuid(char *ptr, char *uuid);
void process_logged_in_data(char *buffer);

/* handle_protocol */
void handle_protocol(char *buffer);

/* parse_user */
void parse_users(char *buffer);

/* str_to_word_array */
char **str_to_word_array(char *str);
void free_arr(char **arr);

/* array_to_string */
char *array_to_string(char **words, size_t num_words);

// RESPONSE

/* response_initialisation */
void response_initialisation(char **args);

/* response_login */
void response_login(char **args);
void response_logout(char **args);

/* response_send */
void response_send(char **args);
void response_bad_send(char **args);

/* response_user */
void response_user(char **args);
void response_bad_user(char **args);
void response_users(char **args);

/* response_messages */
void response_messages(char **args);
void response_bad_messages(char **args);

/* tokenize */
char **tokenize(char *buffer, int *count);
void free_tokenize(char **arr, int count);
void add_null_terminator(char ***args, int *count);

ssize_t read_c(ssize_t bytes_received, int client_socket,
    char *buffer, size_t bytes_rcvd);

/* remove_char */
void remove_char(char *str, char c);

#endif /* !CLIENT_H_ */
