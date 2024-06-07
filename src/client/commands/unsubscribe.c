/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** unsubscribe
*/

#include "client.h"

void unsubscribe(client_t *client)
{
    const char *team_uuid = client->arguments[0];

    dprintf(client->socket, "/unsubscribe/%s/\n", team_uuid);
}
