/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** init_server
*/

#include "server.h"

void bind_and_listen(const server_t *server)
{
    const struct sockaddr *addr =
        (const struct sockaddr *)&server->server_addr;

    if (bind(server->server_socket, addr, server->server_addr_len) == -1) {
        exit_error("Bind failed");
    }
    if (listen(server->server_socket, 5) == -1) {
        exit_error("Listen failed");
    }
    printf("Server listening on port %hu\n", server->port);
}

void init_fds(server_t *server)
{
    clients_t *client = NULL;

    FD_ZERO(&server->read_fds);
    FD_SET(server->server_socket, &server->read_fds);
    LIST_FOREACH(client, &server->clients, pointers) {
        FD_SET(client->socket, &server->read_fds);
    }
}

void init_server(server_t *server, uint16_t port)
{
    server->port = port;
    server->max_fd = 0;
    LIST_INIT(&server->clients);
    LIST_INIT(&server->teams);
    server->server_addr = (struct sockaddr_in){0};
    server->server_addr_len = sizeof(server->server_addr);
    server->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    init_fds(server);
    if (server->server_socket == -1) {
        exit_error("Socket creation failed");
    }
    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_port = htons(port);
    server->server_addr.sin_addr.s_addr = INADDR_ANY;
    bind_and_listen(server);
    load_clients(server);
    load_teams(server);
    load_channels(server);
}
