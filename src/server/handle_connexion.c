/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-vincent.montero-fontaine
** File description:
** handle_connexion
*/
#include "server.h"

void access_db(database_t *db)
{
    if (db == NULL)
        exit(84);
    if (access("database/myteams.db", F_OK) != -1) {
        load_from_db("database/myteams.db", db);
        print_db_contents("database/myteams.db", db);
    } else
        initialize_database(db);
}

//!Should exit pour gérer le CTRL + C
void handle_connections(int s)
{
    log_t log;

    memset(&log, 0, sizeof(log_t));
    log.max_sd = s;
    process_file("database/login.db");
    while (1) {
        FD_ZERO(&log.readfds);
        FD_SET(s, &log.readfds);
        for (int i = 0; i < MAX_CLIENTS; i++)
            set_client_socket(&log, i);
        select_client(&log, s);
    }
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (log.clients[i].sd > 0 && FD_ISSET(log.clients[i].sd, &log.readfds))
            logout_cmd(&log, &log.clients[i], NULL);
    }
}

void select_client(log_t *logins, int s)
{
    int rc;
    socklen_t clientSze;
    int clientSocket;
    struct sockaddr_in clientSa;

    rc = select(logins->max_sd + 1, &logins->readfds, NULL, NULL, NULL);
    if (rc < 0)
        return;
    if (FD_ISSET(s, &logins->readfds)) {
        clientSze = sizeof(clientSa);
        clientSocket = accept(s, (struct sockaddr *)&clientSa, &clientSze);
        if (clientSocket < 0)
            return;
        add_client_socket(clientSocket, logins, &clientSa);
        my_putstr_fd("220 Service ready for new user.\r\n", clientSocket);
    }
    handle_client_data(logins);
}
