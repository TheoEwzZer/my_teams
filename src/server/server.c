/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** server
*/

#include "server.h"

server_t *current_server;

int handle_read(clients_t *client)
{
    ssize_t bytes_read = 0;
    char *newline = NULL;

    bytes_read = recv(client->socket, client->command,
        MAX_COMMAND_LENGTH - 1, 0);
    if ((bytes_read <= 0) && (errno != EAGAIN)) {
        client->need_exit = true;
        return 1;
    }
    client->command[bytes_read] = '\0';
    newline = strchr(client->command, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }
    return (client->socket == -1) ? 1 : 0;
}

void loop_server(server_t *server)
{
    server->max_fd = server->server_socket;
    while (1) {
        select_accept(server);
        check_clients(server);
        handle_disconnection(server);
    }
}

void sigint_handler(int signum)
{
    if (signum != SIGINT) {
        return;
    }
    save(current_server);
    free_server(current_server);
    exit(0);
}

int server(uint16_t port)
{
    server_t *server = malloc(sizeof(server_t));

    current_server = server;
    signal(SIGINT, sigint_handler);
    init_server(server, port);
    loop_server(server);
    free_server(server);
}
