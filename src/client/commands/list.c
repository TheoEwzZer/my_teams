/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** list
*/

#include "client.h"

void list(client_t *client)
{
    const char *team = client->context[0];
    const char *channel = client->context[1];
    const char *thread = client->context[2];
    size_t context_count = count_contexts(client);

    if (context_count == 0) {
        dprintf(client->socket, "/list_teams/\n");
    }
    if (context_count == 1) {
        dprintf(client->socket, "/list_channels/%s/\n", team);
    }
    if (context_count == 2) {
        dprintf(client->socket, "/list_threads/%s/%s/\n", team, channel);
    }
    if (context_count == 3) {
        dprintf(client->socket, "/list_replies/%s/%s/%s/\n",
            team, channel, thread);
    }
}
