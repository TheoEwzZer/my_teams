/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** user
*/

#include "client.h"

void send_message(client_t *client)
{
    const char *sender_uuid = client->uuid_str;
    const char *receiver_uuid = client->arguments[0];
    const char *message_body = client->arguments[1];

    dprintf(client->socket, "/send/%s/%s/%s/\n",
        sender_uuid, receiver_uuid, message_body);
}
