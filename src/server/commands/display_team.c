/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** display_team
*/

#include "server.h"

void display_team(server_t *server, clients_t *client)
{
    const char *team_uuid = client->arguments[0];
    teams_t *current_team = NULL;

    LIST_FOREACH(current_team, &server->teams, pointers) {
        if (strcmp(current_team->uuid_str, team_uuid) == 0) {
            dprintf(client->socket, "client_print_team\n%s\n%s\n%s\n",
                current_team->uuid_str, current_team->name,
                current_team->description);
            return;
        }
    }
    dprintf(client->socket, "client_error_unknown_team\n%s\n", team_uuid);
}
