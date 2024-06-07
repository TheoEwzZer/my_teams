/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** user
*/

#include "server.h"

clients_t *find_client_by_uuid(server_t *server, const uuid_t uuid)
{
    clients_t *current_client = NULL;

    LIST_FOREACH(current_client, &server->clients, pointers) {
        if (uuid_compare(current_client->uuid, uuid) == 0) {
            return current_client;
        }
    }
    return NULL;
}

void user(server_t *server, clients_t *client)
{
    const char *user_uuid = client->arguments[0];
    uuid_t uuid = {0};
    clients_t *found_client = NULL;

    if (uuid_parse(user_uuid, uuid) == -1) {
        dprintf(client->socket, "client_error_unknown_user\n%s\n", user_uuid);
        return;
    }
    found_client = find_client_by_uuid(server, uuid);
    if (found_client == NULL) {
        dprintf(client->socket, "client_error_unknown_user\n%s\n", user_uuid);
        return;
    }
    dprintf(client->socket, "client_print_user\n%s\n%s\n%d\n",
        user_uuid, found_client->name, found_client->status);
}
