/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** handle_disconnection
*/

#include <server.h>

void disconnect_client(server_t *server, clients_t *client)
{
    FD_CLR(client->socket, &server->read_fds);
    if (client->name[0] != '\0') {
        server_event_user_logged_out(client->uuid_str);
    }
    close(client->socket);
    client->socket = -1;
    client->status = 0;
}

void handle_disconnection(server_t *server)
{
    clients_t *current_client = LIST_FIRST(&server->clients);
    clients_t *next_client = NULL;

    while (current_client != NULL) {
        next_client = LIST_NEXT(current_client, pointers);
        if (FD_ISSET(current_client->socket, &server->read_fds)
            && current_client->need_exit) {
            disconnect_client(server, current_client);
        }
        current_client = next_client;
    }
}
