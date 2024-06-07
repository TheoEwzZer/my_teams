/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** list_channels
*/

#include "server.h"

void list_channels(server_t *server, clients_t *client)
{
    const char *team_uuid = client->arguments[0];
    teams_t *team = get_team_by_uuid(server, team_uuid);
    struct timespec ts = {.tv_sec = 0, .tv_nsec = 100000000L};
    channel_t *current_channel = NULL;

    if (team == NULL) {
        dprintf(client->socket, "client_error_unknown_team\n%s\n", team_uuid);
        return;
    }
    LIST_FOREACH(current_channel, &team->channels, pointers) {
        dprintf(client->socket, "client_team_print_channels\n%s\n%s\n%s\n",
            current_channel->uuid_str,
            current_channel->name,
            current_channel->description
        );
        nanosleep(&ts, NULL);
    }
}
