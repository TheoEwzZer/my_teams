/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** logging_team
*/

#include "client.h"

void handle_event_team_created(client_t *client, const regmatch_t *matches)
{
    char team_uuid[UUID_LENGTH] = {0};
    char team_name[MAX_NAME_LENGTH] = {0};
    char team_desc[MAX_DESCRIPTION_LENGTH] = {0};

    memcpy(team_uuid, &client->server_response[matches[1].rm_so],
        (size_t)matches[1].rm_eo - (size_t)matches[1].rm_so);
    team_uuid[UUID_LENGTH - 1] = '\0';
    memcpy(team_name, &client->server_response[matches[2].rm_so],
        (size_t)matches[2].rm_eo - (size_t)matches[2].rm_so);
    team_name[matches[2].rm_eo - matches[2].rm_so] = '\0';
    memcpy(team_desc, &client->server_response[matches[3].rm_so],
        (size_t)matches[3].rm_eo - (size_t)matches[3].rm_so);
    team_desc[matches[3].rm_eo - matches[3].rm_so] = '\0';
    client_event_team_created(team_uuid, team_name, team_desc);
}

void handle_print_team_created(client_t *client, const regmatch_t *matches)
{
    char team_uuid[UUID_LENGTH] = {0};
    char team_name[MAX_NAME_LENGTH] = {0};
    char team_desc[MAX_DESCRIPTION_LENGTH] = {0};

    memcpy(team_uuid, &client->server_response[matches[1].rm_so],
        (size_t)matches[1].rm_eo - (size_t)matches[1].rm_so);
    team_uuid[UUID_LENGTH - 1] = '\0';
    memcpy(team_name, &client->server_response[matches[2].rm_so],
        (size_t)matches[2].rm_eo - (size_t)matches[2].rm_so);
    team_name[matches[2].rm_eo - matches[2].rm_so] = '\0';
    memcpy(team_desc, &client->server_response[matches[3].rm_so],
        (size_t)matches[3].rm_eo - (size_t)matches[3].rm_so);
    team_desc[matches[3].rm_eo - matches[3].rm_so] = '\0';
    client_print_team_created(team_uuid, team_name, team_desc);
}

void handle_print_team(client_t *client, const regmatch_t *matches)
{
    char team_uuid[UUID_LENGTH] = {0};
    char team_name[MAX_NAME_LENGTH] = {0};
    char team_desc[MAX_DESCRIPTION_LENGTH] = {0};

    memcpy(team_uuid, &client->server_response[matches[1].rm_so],
        (size_t)matches[1].rm_eo - (size_t)matches[1].rm_so);
    team_uuid[UUID_LENGTH - 1] = '\0';
    memcpy(team_name, &client->server_response[matches[2].rm_so],
        (size_t)matches[2].rm_eo - (size_t)matches[2].rm_so);
    team_name[matches[2].rm_eo - matches[2].rm_so] = '\0';
    memcpy(team_desc, &client->server_response[matches[3].rm_so],
        (size_t)matches[3].rm_eo - (size_t)matches[3].rm_so);
    team_desc[matches[3].rm_eo - matches[3].rm_so] = '\0';
    client_print_team(team_uuid, team_name, team_desc);
}

void handle_print_teams(client_t *client, const regmatch_t *matches)
{
    char team_uuid[UUID_LENGTH] = {0};
    char team_name[MAX_NAME_LENGTH] = {0};
    char team_desc[MAX_DESCRIPTION_LENGTH] = {0};

    memcpy(team_uuid, &client->server_response[matches[1].rm_so],
        (size_t)matches[1].rm_eo - (size_t)matches[1].rm_so);
    team_uuid[UUID_LENGTH - 1] = '\0';
    memcpy(team_name, &client->server_response[matches[2].rm_so],
        (size_t)matches[2].rm_eo - (size_t)matches[2].rm_so);
    team_name[matches[2].rm_eo - matches[2].rm_so] = '\0';
    memcpy(team_desc, &client->server_response[matches[3].rm_so],
        (size_t)matches[3].rm_eo - (size_t)matches[3].rm_so);
    team_desc[matches[3].rm_eo - matches[3].rm_so] = '\0';
    client_print_teams(team_uuid, team_name, team_desc);
}
