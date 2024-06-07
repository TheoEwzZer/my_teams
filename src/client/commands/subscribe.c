/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** subscribe
*/

#include "client.h"

void subscribe(client_t *client)
{
    const char *team_uuid = client->arguments[0];

    dprintf(client->socket, "/subscribe/%s/\n", team_uuid);
}
