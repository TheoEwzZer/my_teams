/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** users
*/

#include "server.h"

void list_teams(server_t *server, clients_t *client)
{
    teams_t *current_team = NULL;
    struct timespec ts = {.tv_sec = 0, .tv_nsec = 100000000L};

    LIST_FOREACH(current_team, &server->teams, pointers) {
        dprintf(client->socket, "client_print_teams\n%s\n%s\n%s\n",
            current_team->uuid_str,
            current_team->name,
            current_team->description
        );
        nanosleep(&ts, NULL);
    }
}
