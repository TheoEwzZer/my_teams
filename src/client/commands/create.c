/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** create
*/

#include "client.h"

void create(client_t *client)
{
    const char *fst = client->arguments[0];
    const char *snd = client->arguments[1];
    size_t context_count = count_contexts(client);

    if (context_count == 0) {
        dprintf(client->socket, "/create_team/%s/%s/\n", fst, snd);
    }
    if (context_count == 1) {
        dprintf(client->socket, "/create_channel/%s/%s/%s\n",
            fst, snd, client->context[0]);
    }
    if (context_count == 2) {
        dprintf(client->socket, "/create_thread/%s/%s/%s/%s/\n",
            fst, snd, client->context[0], client->context[1]);
    }
    if (context_count == 3) {
        dprintf(client->socket,
            "/create_comment/%s/%s/%s/%s/%s/\n", fst, snd,
            client->context[0], client->context[1], client->context[2]);
    }
}
