/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** users
*/

#include "client.h"

void users(client_t *client)
{
    (void)client;
    dprintf(client->socket, "/users\n");
}
