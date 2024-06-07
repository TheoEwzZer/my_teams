/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** free
*/

#include "client.h"

void free_arg(client_t *client)
{
    for (size_t i = 0; i < MAX_ARGS; i++) {
        free(client->arguments[i]);
    }
}

void free_client(client_t *client)
{
    close(client->socket);
    uuid_clear(client->uuid);
    free(client->uuid_str);
    free(client);
    exit(0);
}
