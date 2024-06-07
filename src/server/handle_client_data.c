/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_client_data
*/

#include "server.h"

void handle_client(server_t *server, clients_t **client_ptr)
{
    clients_t *current_client = *client_ptr;

    if (current_client->socket == -1) {
        return;
    }
    if (!FD_ISSET(current_client->socket, &server->read_fds)) {
        return;
    }
    if (handle_read(current_client) == 1) {
        return;
    }
    handle_command(server, current_client);
}

void check_clients(server_t *server)
{
    clients_t *client = NULL;

    LIST_FOREACH(client, &server->clients, pointers) {
        handle_client(server, &client);
    }
    LIST_FOREACH(client, &server->clients, pointers) {
        if ((client->status == 0) || (client->socket == -1)) {
            continue;
        }
        display_pending_messages(client);
    }
}
