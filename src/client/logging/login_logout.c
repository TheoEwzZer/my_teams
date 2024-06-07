/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** logging
*/

#include "client.h"

void handle_logged_in(client_t *client, const regmatch_t *matches)
{
    char user_uuid[UUID_LENGTH] = {0};
    char user_name[MAX_NAME_LENGTH] = {0};

    memcpy(user_uuid, &client->server_response[matches[1].rm_so],
        (size_t)matches[1].rm_eo - (size_t)matches[1].rm_so);
    user_uuid[36] = '\0';
    memcpy(user_name, &client->server_response[matches[2].rm_so],
        (size_t)matches[2].rm_eo - (size_t)matches[2].rm_so);
    user_name[matches[2].rm_eo - matches[2].rm_so] = '\0';
    client_event_logged_in(user_uuid, user_name);
}

void handle_logged_out(client_t *client, const regmatch_t *matches)
{
    char user_uuid[UUID_LENGTH] = {0};
    char user_name[MAX_NAME_LENGTH] = {0};

    memcpy(user_uuid, &client->server_response[matches[1].rm_so],
        (size_t)matches[1].rm_eo - (size_t)matches[1].rm_so);
    user_uuid[36] = '\0';
    memcpy(user_name, &client->server_response[matches[2].rm_so],
        (size_t)matches[2].rm_eo - (size_t)matches[2].rm_so);
    user_name[matches[2].rm_eo - matches[2].rm_so] = '\0';
    client_event_logged_out(user_uuid, user_name);
    if (strcmp(user_uuid, client->uuid_str) == 0) {
        free_client(client);
    }
}
