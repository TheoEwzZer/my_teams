/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** info
*/

#include "client.h"

void info(client_t *client)
{
    const char *team = client->context[0];
    const char *channel = client->context[1];
    const char *thread = client->context[2];
    size_t context_count = count_contexts(client);

    if (context_count == 0) {
        client_print_user(client->uuid_str, client->name, client->status);
    }
    if (context_count == 1) {
        dprintf(client->socket, "/display_team/%s/\n", team);
    }
    if (context_count == 2) {
        dprintf(client->socket, "/display_channel/%s/%s/\n", team, channel);
    }
    if (context_count == 3) {
        dprintf(client->socket, "/display_thread/%s/%s/%s/\n",
            team, channel, thread);
    }
}
