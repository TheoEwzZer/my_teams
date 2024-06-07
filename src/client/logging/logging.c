/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** logging
*/

#include "client.h"

void handle_print_user(client_t *client, const regmatch_t *matches)
{
    char user_uuid[UUID_LENGTH] = {0};
    char user_name[MAX_NAME_LENGTH] = {0};
    char user_status[2] = {0};
    char *endptr = NULL;
    long status = 0;

    memcpy(user_uuid, &client->server_response[matches[1].rm_so],
        (size_t)matches[1].rm_eo - (size_t)matches[1].rm_so);
    user_uuid[36] = '\0';
    memcpy(user_name, &client->server_response[matches[2].rm_so],
        (size_t)matches[2].rm_eo - (size_t)matches[2].rm_so);
    user_name[matches[2].rm_eo - matches[2].rm_so] = '\0';
    memcpy(user_status, &client->server_response[matches[3].rm_so],
        (size_t)matches[3].rm_eo - (size_t)matches[3].rm_so);
    user_status[matches[3].rm_eo - matches[3].rm_so] = '\0';
    status = strtol(user_status, &endptr, 10);
    if (endptr == user_status) {
        return;
    }
    client_print_user(user_uuid, user_name, (int)status);
}

void handle_print_users(client_t *client, const regmatch_t *matches)
{
    char user_uuid[UUID_LENGTH] = {0};
    char user_name[MAX_NAME_LENGTH] = {0};
    char user_status[2] = {0};
    char *endptr = NULL;
    long status = 0;

    memcpy(user_uuid, &client->server_response[matches[1].rm_so],
        (size_t)matches[1].rm_eo - (size_t)matches[1].rm_so);
    user_uuid[36] = '\0';
    memcpy(user_name, &client->server_response[matches[2].rm_so],
        (size_t)matches[2].rm_eo - (size_t)matches[2].rm_so);
    user_name[matches[2].rm_eo - matches[2].rm_so] = '\0';
    memcpy(user_status, &client->server_response[matches[3].rm_so],
        (size_t)matches[3].rm_eo - (size_t)matches[3].rm_so);
    user_status[matches[3].rm_eo - matches[3].rm_so] = '\0';
    status = strtol(user_status, &endptr, 10);
    if (endptr == user_status) {
        return;
    }
    client_print_users(user_uuid, user_name, (int)status);
}

void handle_message_received(client_t *client, const regmatch_t *matches)
{
    char user_uuid[UUID_LENGTH] = {0};
    char message_body[MAX_BODY_LENGTH] = {0};

    memcpy(user_uuid, &client->server_response[matches[1].rm_so],
        (size_t)matches[1].rm_eo - (size_t)matches[1].rm_so);
    user_uuid[36] = '\0';
    memcpy(message_body, &client->server_response[matches[2].rm_so],
        (size_t)matches[2].rm_eo - (size_t)matches[2].rm_so);
    message_body[matches[2].rm_eo - matches[2].rm_so] = '\0';
    client_event_private_message_received(user_uuid, message_body);
}

void handle_private_message_print(client_t *client, const regmatch_t *matches)
{
    char sender_uuid[UUID_LENGTH] = {0};
    char message_body[MAX_BODY_LENGTH] = {0};
    char time_str[11] = {0};
    char *endptr = NULL;
    time_t time = 0;

    memcpy(sender_uuid, &client->server_response[matches[1].rm_so],
        (size_t)matches[1].rm_eo - (size_t)matches[1].rm_so);
    sender_uuid[36] = '\0';
    memcpy(time_str, &client->server_response[matches[2].rm_so],
        (size_t)matches[2].rm_eo - (size_t)matches[2].rm_so);
    time_str[10] = '\0';
    memcpy(message_body, &client->server_response[matches[3].rm_so],
        (size_t)matches[3].rm_eo - (size_t)matches[3].rm_so);
    message_body[matches[3].rm_eo - matches[3].rm_so] = '\0';
    time = strtol(time_str, &endptr, 10);
    if (endptr == time_str) {
        return;
    }
    client_private_message_print_messages(sender_uuid, time, message_body);
}
