/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** logging_error
*/

#include "client.h"

void handle_unknown_user(client_t *client, const regmatch_t *matches)
{
    char user_uuid[UUID_LENGTH] = {0};

    memcpy(user_uuid, &client->server_response[matches[1].rm_so],
        (size_t)matches[1].rm_eo - (size_t)matches[1].rm_so);
    user_uuid[36] = '\0';
    client_error_unknown_user(user_uuid);
}

void handle_already_exist(client_t *client, const regmatch_t *matches)
{
    (void)client;
    (void)matches;
    client_error_already_exist();
}

void handle_unknown_team(client_t *client, const regmatch_t *matches)
{
    char team_uuid[UUID_LENGTH] = {0};

    memcpy(team_uuid, &client->server_response[matches[1].rm_so],
        (size_t)matches[1].rm_eo - (size_t)matches[1].rm_so);
    team_uuid[36] = '\0';
    client_error_unknown_team(team_uuid);
}

void handle_unknown_channel(client_t *client, const regmatch_t *matches)
{
    char channel_uuid[UUID_LENGTH] = {0};

    memcpy(channel_uuid, &client->server_response[matches[1].rm_so],
        (size_t)matches[1].rm_eo - (size_t)matches[1].rm_so);
    channel_uuid[36] = '\0';
    client_error_unknown_channel(channel_uuid);
}
