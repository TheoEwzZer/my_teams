/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** user
*/

#include "client.h"

void user(client_t *client)
{
    const char *user_uuid = client->arguments[0];

    dprintf(client->socket, "/user/%s/\n", user_uuid);
}
