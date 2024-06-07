/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** select_accept
*/

#include "server.h"

void add_new_client(server_t *server, int client_socket)
{
    clients_t *new_client = malloc(sizeof(clients_t));

    memset(new_client->command, 0, MAX_COMMAND_LENGTH);
    memset(new_client->name, 0, MAX_NAME_LENGTH);
    new_client->need_exit = false;
    new_client->socket = client_socket;
    new_client->status = 0;
    LIST_INSERT_HEAD(&server->clients, new_client, pointers);
    TAILQ_INIT(&new_client->messages);
}

void select_accept(server_t *server)
{
    int client_sock = 0;
    struct sockaddr *addr = (struct sockaddr *)&server->server_addr;

    init_fds(server);
    if (select(server->max_fd + 1, &server->read_fds,
        NULL, NULL, NULL) == -1) {
        return;
    }
    if (!FD_ISSET(server->server_socket, &server->read_fds)) {
        return;
    }
    client_sock = accept(server->server_socket,
        addr, &server->server_addr_len);
    if (client_sock == -1)
        exit_error("Accept failed");
    if (client_sock > server->max_fd) {
        server->max_fd = client_sock;
    }
    add_new_client(server, client_sock);
}
