/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** logout
*/

#include "client.h"

void logout(client_t *client)
{
    const char *user_name = client->name;
    const char *user_uuid = client->uuid_str;

    dprintf(client->socket, "/logout/%s/%s/\n", user_name, user_uuid);
}
