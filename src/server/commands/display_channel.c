/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** display_team
*/

#include "server.h"

void display_channel(server_t *server, clients_t *client)
{
    const char *team_uuid = client->arguments[0];
    const char *channel_uuid = client->arguments[1];
    teams_t *team = get_team_by_uuid(server, team_uuid);
    channel_t *channel = get_channel_by_uuid(team, channel_uuid);

    if (team == NULL) {
        dprintf(client->socket, "client_error_unknown_team\n%s\n", team_uuid);
        return;
    }
    if (channel == NULL) {
        dprintf(client->socket, "client_error_unknown_channel\n%s\n",
            channel_uuid);
        return;
    }
    dprintf(client->socket, "client_print_channel\n%s\n%s\n%s\n",
        channel->uuid_str, channel->name, channel->description);
}
