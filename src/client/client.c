/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** client
*/

#include "client.h"

const api_t APIS[20] = {
    {
        "client_event_logged_in\n([^/\n]+)\n([^/\n]+)",
        handle_logged_in
    },
    {
        "client_event_logged_out\n([^/\n]+)\n([^/\n]+)",
        handle_logged_out
    },
    {
        "client_print_user\n([^/\n]+)\n([^/\n]+)\n([0-9]+)",
        handle_print_user
    },
    {
        "client_print_users\n([^/\n]+)\n([^/\n]+)\n([0-9]+)",
        handle_print_users
    },
    {
        "client_error_unknown_user\n([^/\n]+)",
        handle_unknown_user
    },
    {
        "client_event_private_message_received\n([^/\n]+)\n([^/\n]+)",
        handle_message_received
    },
    {
        "client_private_message_print\n([^/\n]+)\n([^/\n]+)\n([^/\n]+)",
        handle_private_message_print
    },
    {
        "client_error_already_exist\n",
        handle_already_exist
    },
    {
        "client_event_team_created\n([^/\n]+)\n([^/\n]+)\n([^/\n]+)",
        handle_event_team_created
    },
    {
        "client_print_team_created\n([^/\n]+)\n([^/\n]+)\n([^/\n]+)",
        handle_print_team_created
    },
    {
        "client_error_unknown_team\n([^/\n]+)",
        handle_unknown_team
    },
    {
        "client_print_team\n([^/\n]+)\n([^/\n]+)\n([^/\n]+)",
        handle_print_team
    },
    {
        "client_print_teams\n([^/\n]+)\n([^/\n]+)\n([^/\n]+)",
        handle_print_teams
    },
    {
        "client_print_channel_created\n([^/\n]+)\n([^/\n]+)\n([^/\n]+)",
        handle_print_channel_created
    },
    {
        "client_event_channel_created\n([^/\n]+)\n([^/\n]+)\n([^/\n]+)",
        handle_event_channel_created
    },
    {
        "client_print_subscribed\n([^/\n]+)\n([^/\n]+)",
        handle_print_subscribed
    },
    {
        "client_print_unsubscribed\n([^/\n]+)\n([^/\n]+)",
        handle_print_unsubscribed
    },
    {
        "client_error_unknown_channel\n([^/\n]+)",
        handle_unknown_channel
    },
    {
        "client_print_channel\n([^/\n]+)\n([^/\n]+)\n([^/\n]+)",
        handle_print_channel
    },
    {
        "client_team_print_channels\n([^/\n]+)\n([^/\n]+)\n([^/\n]+)",
        handle_team_print_channels
    },
};

client_t *current_client = NULL;

void handle_server_response(client_t *client)
{
    regex_t regex = {0};
    regmatch_t matches[4] = {0};

    memset(client->server_response, 0, MAX_COMMAND_LENGTH);
    recv(client->socket, client->server_response, MAX_COMMAND_LENGTH, 0);
    for (size_t i = 0; i < (sizeof(APIS) / sizeof(api_t)); i++) {
        regcomp(&regex, APIS[i].api_regex, REG_EXTENDED);
        if (regexec(&regex, client->server_response, 4, matches, 0) == 0) {
            APIS[i].handler(client, matches);
        }
        regfree(&regex);
    }
}

void handle_input(client_t *client)
{
    char buffer[MAX_COMMAND_LENGTH] = {0};
    ssize_t nbytes = read(STDIN_FILENO, buffer, MAX_COMMAND_LENGTH - 1);

    memset(client->command_buffer, 0, MAX_COMMAND_LENGTH);
    if (nbytes <= 0) {
        return;
    }
    strcat(client->command_buffer, buffer);
    while ((nbytes > 0) && (buffer[nbytes - 1] != '\n')) {
        nbytes = read(STDIN_FILENO, buffer, MAX_COMMAND_LENGTH - 1);
        strcat(client->command_buffer, buffer);
    }
    if (strchr(client->command_buffer, '\n') != NULL) {
        strcpy(client->command, client->command_buffer);
        memset(client->command_buffer, 0, MAX_COMMAND_LENGTH);
        handle_client_command(client);
    }
}

void handle_io(client_t *client, int client_socket)
{
    fd_set read_fds = {0};

    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);
    FD_SET(client_socket, &read_fds);
    client->max_fd = (STDIN_FILENO > client_socket) ? 0 : client_socket;
    if (select(client->max_fd + 1, &read_fds, NULL, NULL, NULL) == -1) {
        return;
    }
    if (FD_ISSET(STDIN_FILENO, &read_fds)) {
        handle_input(client);
    }
    if (FD_ISSET(client_socket, &read_fds)) {
        handle_server_response(client);
    }
}

void sigint_handler(int signum)
{
    if (signum != SIGINT) {
        return;
    }
    if (current_client != NULL) {
        if (current_client->status == 1) {
            logout(current_client);
        }
        close(current_client->socket);
        free(current_client);
    }
    exit(0);
}

int client(const char *ip, uint16_t port)
{
    client_t *client = NULL;
    int client_socket = connect_to_server(ip, port);

    if (client_socket == -1) {
        return 84;
    }
    client = malloc(sizeof(client_t));
    current_client = client;
    signal(SIGINT, sigint_handler);
    printf("Connecting to server at %s on port %d\n", ip, port);
    client->socket = client_socket;
    client->status = 0;
    client->max_fd = 0;
    for (size_t i = 0; i < MAX_ARGS; i++) {
        client->context[i] = strdup("");
    }
    while (1) {
        handle_io(client, client_socket);
    }
    return 0;
}
