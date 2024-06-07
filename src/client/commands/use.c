/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** user
*/

#include "client.h"

void use_default(client_t *client)
{
    client->context[0] = strdup("");
    client->context[1] = strdup("");
    client->context[2] = strdup("");
}

void use_team(client_t *client)
{
    const char *team_uuid = client->arguments[0];

    client->context[0] = strdup(team_uuid);
    client->context[1] = strdup("");
    client->context[2] = strdup("");
}

void use_channel(client_t *client)
{
    const char *team_uuid = client->arguments[0];
    const char *channel_body = client->arguments[1];

    client->context[0] = strdup(team_uuid);
    client->context[1] = strdup(channel_body);
    client->context[2] = strdup("");
}

void use_thread(client_t *client)
{
    const char *team_uuid = client->arguments[0];
    const char *channel_body = client->arguments[1];
    const char *thread_body = client->arguments[2];

    client->context[0] = strdup(team_uuid);
    client->context[1] = strdup(channel_body);
    client->context[2] = strdup(thread_body);
}
