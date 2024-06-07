/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** logging_channel
*/

#include "client.h"

void handle_print_channel_created(client_t *client, const regmatch_t *matches)
{
    char channel_uuid[UUID_LENGTH] = {0};
    char channel_name[MAX_NAME_LENGTH] = {0};
    char channel_desc[MAX_DESCRIPTION_LENGTH] = {0};

    memcpy(channel_uuid, &client->server_response[matches[1].rm_so],
        (size_t)matches[1].rm_eo - (size_t)matches[1].rm_so);
    channel_uuid[UUID_LENGTH - 1] = '\0';
    memcpy(channel_name, &client->server_response[matches[2].rm_so],
        (size_t)matches[2].rm_eo - (size_t)matches[2].rm_so);
    channel_name[matches[2].rm_eo - matches[2].rm_so] = '\0';
    memcpy(channel_desc, &client->server_response[matches[3].rm_so],
        (size_t)matches[3].rm_eo - (size_t)matches[3].rm_so);
    channel_desc[matches[3].rm_eo - matches[3].rm_so] = '\0';
    client_print_channel_created(channel_uuid, channel_name, channel_desc);
}

void handle_event_channel_created(client_t *client, const regmatch_t *matches)
{
    char channel_uuid[UUID_LENGTH] = {0};
    char channel_name[MAX_NAME_LENGTH] = {0};
    char channel_desc[MAX_DESCRIPTION_LENGTH] = {0};

    memcpy(channel_uuid, &client->server_response[matches[1].rm_so],
        (size_t)matches[1].rm_eo - (size_t)matches[1].rm_so);
    channel_uuid[UUID_LENGTH - 1] = '\0';
    memcpy(channel_name, &client->server_response[matches[2].rm_so],
        (size_t)matches[2].rm_eo - (size_t)matches[2].rm_so);
    channel_name[matches[2].rm_eo - matches[2].rm_so] = '\0';
    memcpy(channel_desc, &client->server_response[matches[3].rm_so],
        (size_t)matches[3].rm_eo - (size_t)matches[3].rm_so);
    channel_desc[matches[3].rm_eo - matches[3].rm_so] = '\0';
    client_event_channel_created(channel_uuid, channel_name, channel_desc);
}

void handle_print_channel(client_t *client, const regmatch_t *matches)
{
    char channel_uuid[UUID_LENGTH] = {0};
    char channel_name[MAX_NAME_LENGTH] = {0};
    char channel_desc[MAX_DESCRIPTION_LENGTH] = {0};

    memcpy(channel_uuid, &client->server_response[matches[1].rm_so],
        (size_t)matches[1].rm_eo - (size_t)matches[1].rm_so);
    channel_uuid[UUID_LENGTH - 1] = '\0';
    memcpy(channel_name, &client->server_response[matches[2].rm_so],
        (size_t)matches[2].rm_eo - (size_t)matches[2].rm_so);
    channel_name[matches[2].rm_eo - matches[2].rm_so] = '\0';
    memcpy(channel_desc, &client->server_response[matches[3].rm_so],
        (size_t)matches[3].rm_eo - (size_t)matches[3].rm_so);
    channel_desc[matches[3].rm_eo - matches[3].rm_so] = '\0';
    client_print_channel(channel_uuid, channel_name, channel_desc);
}

void handle_team_print_channels(client_t *client, const regmatch_t *matches)
{
    char channel_uuid[UUID_LENGTH] = {0};
    char channel_name[MAX_NAME_LENGTH] = {0};
    char channel_desc[MAX_DESCRIPTION_LENGTH] = {0};

    memcpy(channel_uuid, &client->server_response[matches[1].rm_so],
        (size_t)matches[1].rm_eo - (size_t)matches[1].rm_so);
    channel_uuid[UUID_LENGTH - 1] = '\0';
    memcpy(channel_name, &client->server_response[matches[2].rm_so],
        (size_t)matches[2].rm_eo - (size_t)matches[2].rm_so);
    channel_name[matches[2].rm_eo - matches[2].rm_so] = '\0';
    memcpy(channel_desc, &client->server_response[matches[3].rm_so],
        (size_t)matches[3].rm_eo - (size_t)matches[3].rm_so);
    channel_desc[matches[3].rm_eo - matches[3].rm_so] = '\0';
    client_team_print_channels(channel_uuid, channel_name, channel_desc);
}
