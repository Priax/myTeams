/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-vincent.montero-fontaine
** File description:
** ftp
*/

#ifndef FTP_H_
    #define FTP_H_
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <dirent.h>
    #include <ctype.h>
    #include <fcntl.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <sys/select.h>
    #include <sys/wait.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <time.h>
    #include <stdarg.h>
    #include <signal.h>
    #include <uuid/uuid.h>
    #include <sys/queue.h>
    #include "../../libs/myteams/logging_server.h"
    #define MAX_CLIENTS 10
    #define BUFFER_SIZE 1024
    #define LOWER 1024
    #define UPPER 65536
    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define UUID_LENGTH 255
    #define MAX_BODY_LENGTH 512

typedef struct {
    char *buffer;
    char **tokens;
    int token_count;
    int token_start;
    int in_quotes;
} token_t;

typedef struct message {
    char sender[MAX_NAME_LENGTH];
    char body[MAX_BODY_LENGTH];
    TAILQ_ENTRY(message) entries;
} message_t;

typedef struct database {
    TAILQ_HEAD(messages_head, message) messages;
} database_t;

typedef struct client_info {
    int sd;
    int logged_in;
    char *usrnm;
    uuid_t uuid;
    uuid_t team_uuid;
    uuid_t channel_uuid;
    uuid_t thread_uuid;
    char *uuid_str;
} client_info_t;

typedef struct login_s {
    int max_sd;
    fd_set readfds;
    client_info_t clients[MAX_CLIENTS];
    database_t *db;
} log_t;

typedef struct command {
    const char *name;
    void (*func)(log_t *server, client_info_t *client, char **args);
} command_t;

/* my_utils */
int my_strlen(char const *str);
void my_putchar(char c);
void my_putstr(char const *str);
void my_putstr_fd(char const *str, int fd);
void my_putnbr_base(int nb, char const *base);

/* arr_func */
void free_arr(char **arr);
void my_show_word_array(char **arr, char *delim);
int my_lenarr(char **arr);

/* str_to_word_array */
char **str_to_word_array(char *str);
char **str_to_word_array_delim(char *str, char delimiter);

/* handle_command */
void handle_commands(char *buffer, log_t *logins, int i);
void parse_line(const char *line, char *username, char *uuid);

/* read_file */
char *read_file(char *filepath);
char *realloc_if_needed(char *string, size_t *allocated,
    size_t total, size_t *increase);

/* handle_client */
void handle_client_data(log_t *logins);

/* server */
int create_socket(int argc, char **argv);
void add_client_socket(int clientSocket, log_t *logins,
    struct sockaddr_in *clientSa);

/* bind_and_listen */
int bind_socket(int s, char **argv);
int start_listening(int s);

/* handle_connexion */
void handle_connections(int s);

void select_client(log_t *logins, int s);

void read_client(log_t *logins, int i);

/* index */
int get_command_index(char *buffer);

/* quit */
void quit_command(log_t *logins, int i);

/* file */
void transfer_file(FILE *file, int data_socket, int client_sd);
FILE *open_file(char *file_path);

/* accept_connect */
int accept_connec(int data_socket, int client_sd);
int connect_connec(int data_socket, struct sockaddr_in* client_addr);

/* msg */
int find_client_by_uuid(log_t *logins, char *uuid_str);
void msg_command(log_t *log, char *buffer, int i);
void remove_char(char *str, char c);
void cmd_send(log_t *logins, client_info_t *client, char **args);

/* database */
void initialize_database(database_t *db);
void add_message(const char *sender, const char *body, database_t *db);
void save_to_db(const char *filename, database_t *db);
void load_from_db(const char *filename, database_t *db);
void print_db_contents(const char *filename, database_t *db);

/* login */
void login_command(log_t *logins, client_info_t *client, char **args);
int is_whitespace(char c);
int get_uuid_from_username(const char *username, char *uuid_str);

/* tokenize */
char **tokenize(char *buffer, int *count);
void free_tokenize(char **arr, int count);
void add_null_terminator(char ***args, int *count);


/* verify_quoted */
int verify_quoted_args(char *buffer);

/* print_sd_info */
void print_clients_sd(log_t *log);

/* set_socket */
fd_set set_client_socket(log_t *logins, int i);

/* trim_input */
void trim_newline(char *str);
void remove_surrounding_quotes(char *str);

/* is_whitespace */
int is_whitespace(char c);

/* users */
void users_command(log_t *logins, const char *filename, int client_socket);
char *find_line_by_uuid(char *filename, char *uuid);
void user_command(log_t *logins, char *buffer, int client_socket);

/* uuid */
void generate_uuid(char *uuid_str);
char *escape_special_characters(const char *input);
char *read_line(FILE *file);
char *extract_uuid(char *line);
char *find_line_by_uuid(char *filename, char *uuid);

/* process_login */
void process_file(const char *filename);

/* send_all */
void send_message_every_users(log_t *server, char *code, char *args);

/* quotes */
char *delete_quotes(char *str);

/* array_to_string */
char *array_to_string(char **words, size_t num_words);

/* help */
void help_cmd(log_t *logins, client_info_t *client, char **args);

/* logout */
void logout_cmd(log_t *logins, client_info_t *client, char **args);

/* cmd_user */
void cmd_user(log_t *serv, client_info_t *client, char **args);
void cmd_users(log_t *serv, client_info_t *client, char **args);

void cmd_messages(log_t *logins, client_info_t *client, char **args);

/* messages */
void retrieve_messages(const char *sender_uuid,
    const char *receiver_uuid, client_info_t *client);
void store_message(const char *sender_uuid, const char *receiver_uuid,
    const char *message, time_t timestamp);

/* create */
void cmd_create(log_t *server, client_info_t *instance, char **args);

/* send */
void cmd_send_test(log_t *login, client_info_t *client, char **args);

#endif /* !FTP_H_ */
