/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** users
*/

#include "server.h"

void users(server_t *server, clients_t *client)
{
    clients_t *current_client = NULL;
    struct timespec ts = {.tv_sec = 0, .tv_nsec = 100000000L};

    if ((server == NULL) || (client == NULL)) {
        return;
    }
    LIST_FOREACH(current_client, &server->clients, pointers) {
        if ((current_client == NULL) || (current_client->uuid_str == NULL)) {
            continue;
        }
        if (current_client->name[0] == '\0') {
            continue;
        }
        dprintf(client->socket, "client_print_users\n%s\n%s\n%d\n",
            current_client->uuid_str,
            current_client->name,
            current_client->status
        );
        nanosleep(&ts, NULL);
    }
}
