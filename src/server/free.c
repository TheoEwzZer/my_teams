/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** free
*/

#include "server.h"

void free_messages(struct message_list *head)
{
    message_t *current_message = TAILQ_FIRST(head);
    message_t *tmp_message = NULL;

    while (current_message != NULL) {
        tmp_message = TAILQ_NEXT(current_message, pointers);
        TAILQ_REMOVE(head, current_message, pointers);
        free(current_message);
        current_message = tmp_message;
    }
    head->tqh_last = NULL;
    head = NULL;
}

void free_clients(struct client_list *head)
{
    clients_t *current_client = LIST_FIRST(head);
    clients_t *next_client = NULL;

    while (current_client != NULL) {
        next_client = LIST_NEXT(current_client, pointers);
        free_messages(&current_client->messages);
        free(current_client->uuid_str);
        LIST_REMOVE(current_client, pointers);
        free(current_client);
        current_client = next_client;
    }
    head = NULL;
}

void free_teams(struct team_list *head)
{
    teams_t *current_team = LIST_FIRST(head);
    teams_t *next_team = NULL;

    while (current_team != NULL) {
        next_team = LIST_NEXT(current_team, pointers);
        free_channels(&current_team->channels);
        LIST_REMOVE(current_team, pointers);
        free(current_team);
        current_team = next_team;
    }
    head = NULL;
}

void free_channels(struct channel_list *head)
{
    channel_t *current_channel = LIST_FIRST(head);
    channel_t *next_channel = NULL;

    while (current_channel != NULL) {
        next_channel = LIST_NEXT(current_channel, pointers);
        LIST_REMOVE(current_channel, pointers);
        free(current_channel);
        current_channel = next_channel;
    }
    head = NULL;
}

void free_server(server_t *server)
{
    free_clients(&server->clients);
    free_teams(&server->teams);
    close(server->server_socket);
    free(server);
}
