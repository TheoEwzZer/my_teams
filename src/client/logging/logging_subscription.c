/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** logging_subscription
*/

#include "client.h"

void handle_print_subscribed(client_t *client, const regmatch_t *matches)
{
    char team_uuid[UUID_LENGTH] = {0};
    char user_uuid[UUID_LENGTH] = {0};

    memcpy(team_uuid, &client->server_response[matches[1].rm_so],
        (size_t)matches[1].rm_eo - (size_t)matches[1].rm_so);
    team_uuid[UUID_LENGTH - 1] = '\0';
    memcpy(user_uuid, &client->server_response[matches[2].rm_so],
        (size_t)matches[2].rm_eo - (size_t)matches[2].rm_so);
    user_uuid[matches[2].rm_eo - matches[2].rm_so] = '\0';
    server_event_user_subscribed(team_uuid, user_uuid);
}

void handle_print_unsubscribed(client_t *client, const regmatch_t *matches)
{
    char team_uuid[UUID_LENGTH] = {0};
    char user_uuid[UUID_LENGTH] = {0};

    memcpy(team_uuid, &client->server_response[matches[1].rm_so],
        (size_t)matches[1].rm_eo - (size_t)matches[1].rm_so);
    team_uuid[UUID_LENGTH - 1] = '\0';
    memcpy(user_uuid, &client->server_response[matches[2].rm_so],
        (size_t)matches[2].rm_eo - (size_t)matches[2].rm_so);
    user_uuid[matches[2].rm_eo - matches[2].rm_so] = '\0';
    server_event_user_unsubscribed(team_uuid, user_uuid);
}
