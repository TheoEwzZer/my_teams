/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** users
*/

#include "client.h"

void messages(client_t *client)
{
    const char *contact_uuid = client->arguments[0];
    const char *user_uuid = client->uuid_str;

    dprintf(client->socket, "/messages/%s/%s/\n", user_uuid, contact_uuid);
}
