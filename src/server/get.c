/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** get
*/

#include "server.h"

teams_t *get_team_by_uuid(server_t *server, const char *team_uuid)
{
    teams_t *current_team = NULL;

    LIST_FOREACH(current_team, &server->teams, pointers) {
        if (strcmp(current_team->uuid_str, team_uuid) == 0) {
            return current_team;
        }
    }
    return NULL;
}

channel_t *get_channel_by_uuid(teams_t *team, const char *channel_uuid)
{
    channel_t *current_channel = NULL;

    LIST_FOREACH(current_channel, &team->channels, pointers) {
        if (strcmp(current_channel->uuid_str, channel_uuid) == 0) {
            return current_channel;
        }
    }
    return NULL;
}
